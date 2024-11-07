import requests
import sys

if len(sys.argv) > 1:
    file = sys.argv[1]

# Adres URL, na który wysyłasz żądanie DELETE
url = f'http://localhost:8080/delete/{file}'  # Zmienna adres URL na właściwy

# Opcjonalnie możesz dodać nagłówki, jeśli są wymagane (np. token autoryzacyjny)

# Wysłanie żądania DELETE
response = requests.delete(url)

# Sprawdzenie statusu odpowiedzi
if response.status_code == 200:
    print('Zasób został pomyślnie usunięty.')
elif response.status_code == 404:
    print('Zasób nie został znaleziony.')
else:
    print(f'Błąd: {response.status_code}, {response.text}')
