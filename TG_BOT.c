#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <time.h>

#define TELEGRAM_API "https://api.telegram.org/bot"
#define MAX_BUFFER 8192
#define TIMEOUT 5

typedef struct {
    char *data;
    size_t size;
} response_t;

// Callback для получения ответа от API
static size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    response_t *mem = (response_t *)userp;

    char *ptr = realloc(mem->data, mem->size + realsize + 1);
    if (!ptr) {
        printf("Ошибка: недостаточно памяти\n");
        free(mem->data);
        return 0;
    }

    mem->data = ptr;
    memcpy(&(mem->data[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->data[mem->size] = 0;

    return realsize;
}

// Отправка сообщения в Telegram
void send_message(const char *token, const char *chat_id, const char *text) {
    CURL *curl = curl_easy_init();
    if (!curl) return;

    char url[512];
    snprintf(url, sizeof(url), "%s%s/sendMessage", TELEGRAM_API, token);

    response_t response = {malloc(1), 0};

    char data[MAX_BUFFER];
    snprintf(data, sizeof(data), "chat_id=%s&text=%s&parse_mode=HTML", chat_id, text);

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&response);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, TIMEOUT);

    curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    free(response.data);
}

// Проверка доступности портов на роутере
int check_port(const char *host, int port) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) return 0;

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);

    if (inet_pton(AF_INET, host, &addr.sin_addr) <= 0) {
        close(sock);
        return 0;
    }

    // Устанавливаем timeout
    struct timeval tv;
    tv.tv_sec = 2;
    tv.tv_usec = 0;
    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));

    int result = connect(sock, (struct sockaddr *)&addr, sizeof(addr));
    close(sock);
    return (result == 0) ? 1 : 0;
}

// Проверка сетевого подключения (ping)
int check_network(const char *host) {
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "ping -c 1 -W 2 %s > /dev/null 2>&1", host);
    return (system(cmd) == 0) ? 1 : 0;
}

// Сканирование портов
void scan_ports(const char *host, char *result, size_t size) {
    int ports[] = {80, 443, 22, 23, 25, 53, 3306, 5432, 8080, 8443};
    int ports_count = sizeof(ports) / sizeof(ports[0]);
    int open_count = 0;

    strcpy(result, "<b>📊 Результаты сканирования портов:</b>\n\n");
    strcat(result, "Хост: ");
    strcat(result, host);
    strcat(result, "\n");

    for (int i = 0; i < ports_count; i++) {
        char status[128];
        if (check_port(host, ports[i])) {
            snprintf(status, sizeof(status), "✅ Порт %d: <b>ОТКРЫТ</b>\n", ports[i]);
            open_count++;
        } else {
            snprintf(status, sizeof(status), "❌ Порт %d: закрыт\n", ports[i]);
        }
        strncat(result, status, size - strlen(result) - 1);
    }

    char summary[256];
    snprintf(summary, sizeof(summary), "\n<b>Открытых портов:</b> %d/%d", open_count, ports_count);
    strncat(result, summary, size - strlen(result) - 1);
}

// Получение информации о сети
void get_network_info(char *result, size_t size) {
    strcpy(result, "<b>🌐 Информация о сети:</b>\n\n");

    // Получение IP адреса
    FILE *fp = popen("hostname -I 2>/dev/null | awk '{print $1}'", "r");
    if (fp) {
        char ip[64] = "Неизвестно";
        if (fgets(ip, sizeof(ip), fp) != NULL) {
            ip[strcspn(ip, "\n")] = 0;
            strcat(result, "🖥️ Локальный IP: ");
            strcat(result, ip);
            strcat(result, "\n");
        }
        pclose(fp);
    }

    // Получение информации об интерфейсах
    fp = popen("ifconfig 2>/dev/null | grep -E 'inet|RX|TX' | head -10", "r");
    if (fp) {
        char line[256];
        strcat(result, "\n<b>Интерфейсы:</b>\n");
        while (fgets(line, sizeof(line), fp) != NULL && strlen(result) < size - 100) {
            line[strcspn(line, "\n")] = 0;
            strcat(result, line);
            strcat(result, "\n");
        }
        pclose(fp);
    }

    // Получение информации о маршрутизации
    fp = popen("route -n 2>/dev/null | head -5", "r");
    if (fp) {
        char line[256];
        strcat(result, "\n<b>Маршруты:</b>\n");
        while (fgets(line, sizeof(line), fp) != NULL && strlen(result) < size - 100) {
            line[strcspn(line, "\n")] = 0;
            if (strlen(line) > 0)
                strcat(result, line);
            strcat(result, "\n");
        }
        pclose(fp);
    }
}

// Проверка конкретного хоста
void check_host(const char *host, char *result, size_t size) {
    strcpy(result, "<b>🔍 Проверка хоста:</b> ");
    strcat(result, host);
    strcat(result, "\n\n");

    if (check_network(host)) {
        strcat(result, "✅ Хост <b>доступен</b> (ping успешен)\n\n");
        strcat(result, "Дополнительная информация:\n");
        
        // Получаем информацию о хосте
        char cmd[256];
        snprintf(cmd, sizeof(cmd), "nslookup %s 2>/dev/null | grep -A 5 'Name'", host);
        FILE *fp = popen(cmd, "r");
        if (fp) {
            char line[256];
            while (fgets(line, sizeof(line), fp) != NULL && strlen(result) < size - 100) {
                line[strcspn(line, "\n")] = 0;
                if (strlen(line) > 0) {
                    strcat(result, line);
                    strcat(result, "\n");
                }
            }
            pclose(fp);
        }
    } else {
        strcat(result, "❌ Хост <b>недоступен</b> (ping не прошел)\n");
        strcat(result, "Проверьте адрес и сетевое подключение.");
    }
}

// Получение статуса роутера
void get_router_status(const char *router_ip, char *result, size_t size) {
    strcpy(result, "<b>🛡️ Статус роутера Кинетик:</b>\n");
    strcat(result, "IP: ");
    strcat(result, router_ip);
    strcat(result, "\n\n");

    if (check_network(router_ip)) {
        strcat(result, "✅ Роутер <b>в сети</b>\n");
        strcat(result, "🌐 Сетевое соединение: <b>активно</b>\n");
        
        // Проверяем основные сервисы
        strcat(result, "\n<b>Проверка сервисов:</b>\n");
        if (check_port(router_ip, 80)) {
            strcat(result, "✅ HTTP (80): доступен\n");
        }
        if (check_port(router_ip, 443)) {
            strcat(result, "✅ HTTPS (443): доступен\n");
        }
        if (check_port(router_ip, 22)) {
            strcat(result, "✅ SSH (22): доступен\n");
        }
    } else {
        strcat(result, "❌ Роутер <b>недоступен</b>\n");
        strcat(result, "⚠️ Проверьте подключение\n");
    }
}

// Главная функция обработки команд
void handle_command(const char *text, const char *token, const char *chat_id) {
    char response[MAX_BUFFER] = "";
    
    if (strncmp(text, "/start", 6) == 0) {
        strcpy(response, 
            "<b>🤖 Добро пожаловать!</b>\n\n"
            "Я могу помочь вам проверить сеть и порты роутера.\n\n"
            "<b>Доступные команды:</b>\n"
            "/network - информация о сети\n"
            "/router - статус роутера Кинетик\n"
            "/ports - сканирование портов\n"
            "/check &lt;хост&gt; - проверить доступность хоста\n"
            "/scan &lt;IP&gt; - сканировать порты хоста\n"
            "/help - справка\n");
    }
    else if (strncmp(text, "/network", 8) == 0) {
        get_network_info(response, sizeof(response));
    }
    else if (strncmp(text, "/router", 7) == 0) {
        get_router_status("192.168.0.1", response, sizeof(response));
    }
    else if (strncmp(text, "/ports", 6) == 0) {
        scan_ports("192.168.0.1", response, sizeof(response));
    }
    else if (strncmp(text, "/check", 6) == 0) {
        char host[128];
        sscanf(text, "/check %127s", host);
        if (strlen(host) > 0) {
            check_host(host, response, sizeof(response));
        } else {
            strcpy(response, "⚠️ Использование: /check &lt;хост&gt;\nПример: /check google.com");
        }
    }
    else if (strncmp(text, "/scan", 5) == 0) {
        char ip[128];
        sscanf(text, "/scan %127s", ip);
        if (strlen(ip) > 0) {
            scan_ports(ip, response, sizeof(response));
        } else {
            strcpy(response, "⚠️ Использование: /scan &lt;IP&gt;\nПример: /scan 192.168.0.1");
        }
    }
    else if (strncmp(text, "/help", 5) == 0) {
        strcpy(response,
            "<b>📚 Справка</b>\n\n"
            "/start - начало\n"
            "/network - сетевая информация\n"
            "/router - статус роутера\n"
            "/ports - сканирование портов роутера\n"
            "/check &lt;хост&gt; - проверить хост (ping)\n"
            "/scan &lt;IP&gt; - сканировать порты\n"
            "\n<b>Примеры:</b>\n"
            "/check google.com\n"
            "/check 8.8.8.8\n"
            "/scan 192.168.1.1");
    }
    else {
        strcpy(response, "❓ Неизвестная команда.\nНапишите /help для справки.");
    }

    if (strlen(response) > 0) {
        send_message(token, chat_id, response);
    }
}

// Основной цикл бота
void run_bot(const char *token) {
    printf("🤖 Бот запущен. Токен: %s\n", token);
    
    // В реальном приложении здесь будет получение обновлений от Telegram
    // Сейчас это заглушка для демонстрации
    
    CURL *curl = curl_easy_init();
    if (!curl) {
        printf("Ошибка инициализации CURL\n");
        return;
    }

    int offset = 0;
    
    while (1) {
        char url[512];
        snprintf(url, sizeof(url), "%s%s/getUpdates?offset=%d&timeout=30", 
                 TELEGRAM_API, token, offset);

        response_t response = {malloc(1), 0};
        
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&response);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 35L);

        CURLcode res = curl_easy_perform(curl);
        
        if (res == CURLE_OK && response.data && strlen(response.data) > 0) {
            // Парсинг JSON ответа (упрощенный вариант)
            // В боевом коде используйте json-c или jansson
            
            char *update_id_str = strstr(response.data, "\"update_id\":");
            char *text_str = strstr(response.data, "\"text\":\"");
            char *chat_id_str = strstr(response.data, "\"chat\":{\"id\":");

            if (update_id_str && text_str && chat_id_str) {
                int update_id;
                sscanf(update_id_str, "\"update_id\":%d", &update_id);
                offset = update_id + 1;

                // Извлечение текста команды
                char text[512] = "";
                char *text_start = text_str + 8;
                char *text_end = strchr(text_start, '"');
                if (text_end) {
                    size_t len = text_end - text_start;
                    if (len < sizeof(text)) {
                        strncpy(text, text_start, len);
                        text[len] = '\0';
                    }
                }

                // Извлечение chat_id
                char chat_id[64] = "";
                sscanf(chat_id_str, "\"chat\":{\"id\":%63s", chat_id);
                
                // Удаляем лишние символы из chat_id
                char *comma = strchr(chat_id, ',');
                if (comma) *comma = '\0';

                if (strlen(text) > 0 && strlen(chat_id) > 0) {
                    printf("📨 Получена команда: %s от чата: %s\n", text, chat_id);
                    handle_command(text, token, chat_id);
                }
            }
        }

        free(response.data);
        sleep(1);
    }

    curl_easy_cleanup(curl);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Использование: %s <TELEGRAM_BOT_TOKEN>\n", argv[0]);
        printf("Пример: %s 123456789:ABCDefGHIjklmnoPQRstuvWXYZ\n", argv[0]);
        return 1;
    }

    const char *token = argv[1];
    
    printf("╔════════════════════════════════════════╗\n");
    printf("║   Telegram Router Check Bot v1.0      ║\n");
    printf("║   Проверка сети и портов роутера      ║\n");
    printf("╚════════════════════════════════════════╝\n\n");

    run_bot(token);

    return 0;
}
