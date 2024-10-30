import socket
import threading

def send_requests(thread_id, num_requests, log_file):
    host = 'localhost'
    port = 8080
    request = (
        "GET /style.css HTTP/1.1\r\n"
        "Host: localhost:8080\r\n"
        "Connection: keep-alive\r\n"
        'sec-ch-ua-platform: "Linux"\r\n'
        'User-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) '
        'Chrome/130.0.0.0 Safari/537.36\r\n'
        'sec-ch-ua: "Chromium";v="130", "Brave";v="130", "Not?A_Brand";v="99"\r\n'
        'sec-ch-ua-mobile: ?0\r\n'
        "Accept: text/css,*/*;q=0.1\r\n"
        "Sec-GPC: 1\r\n"
        "Accept-Language: en-US,en\r\n"
        "Sec-Fetch-Site: same-origin\r\n"
        "Sec-Fetch-Mode: no-cors\r\n"
        "Sec-Fetch-Dest: style\r\n"
        "Referer: http://localhost:8080/index.html\r\n"
        "Accept-Encoding: gzip, deflate, br, zstd\r\n"
        "\r\n"  # Pusta linia kończąca nagłówki
    )

    for i in range(num_requests):
        try:
            with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
                s.connect((host, port))
                s.sendall(request.encode('utf-8'))

                # Odbieranie odpowiedzi
                response = s.recv(4096)
                # Możesz zapisać odpowiedzi do pliku, jeśli chcesz
                # with open(log_file, 'a') as f:
                #     f.write(f"Thread {thread_id}: Received response: {response.decode('utf-8')}\n")
        except Exception as e:
            with open(log_file, 'a') as f:
                f.write(f"Thread {thread_id}: Connection error: {e}\n")

def main():
    num_threads = 5  # Liczba wątków
    num_requests_per_thread = 1000  # Liczba zapytań na wątek
    log_file = 'connection_errors.log'  # Nazwa pliku do zapisu błędów

    # Opcjonalnie, wyczyść plik błędów przed rozpoczęciem testu
    open(log_file, 'w').close()

    threads = []
    for i in range(num_threads):
        thread = threading.Thread(target=send_requests, args=(i + 1, num_requests_per_thread, log_file))
        threads.append(thread)
        thread.start()

    for thread in threads:
        thread.join()

if __name__ == '__main__':
    main()
