import os
import sys
from datetime import datetime, timedelta
import re

def parse_args(qs):
    if '?' not in qs:
        return
    args_string = qs.split('?')[1]
    args = args_string.split('&')
    for a in args:
        a = a.split('=')
        os.environ[a[0]] = a[1]

def parse_post_args(data):
    args = data.split('&')
    for a in args:
        a = a.split('=')
        os.environ[a[0].strip()] = a[1]

def find_party():
    host_bday = datetime.strptime(os.getenv("your_bday"), "%Y-%m-%d").date()
    user_bday = datetime.strptime(os.getenv("friend_bday"), "%Y-%m-%d").date()
    if host_bday > user_bday:
        distance = (host_bday - user_bday).days
        if distance > 183:
            best_date = host_bday + timedelta(days=int((365 - distance)/2))
        else:
            best_date = host_bday - timedelta(days=int(distance/2))
    else:
        distance = (user_bday - host_bday).days
        if distance > 183:
            best_date = user_bday + timedelta(days=int((365 - distance)/2))
        else:
            best_date = user_bday - timedelta(days=int(distance/2))
    if best_date < datetime.today().date():
        best_date += timedelta(days=365)
    return str(best_date)

def get_files():
    result = ""
    files = os.listdir(f"{os.getcwd()}/src/uploads")
    for file in files:
        if file != "m.png":
            result += f'<a href="{file}" download="{file}">{file}</a><br>'
    return result

def insert_env(line):
    part_one = line.split('{{')[0]
    middle = line.split('{{')[1].split('}}')[0]
    part_two = line.split('}}')[1]
    if middle == "get_files":
        middle = get_files()
    else:
        middle = os.getenv(middle, "")
    return part_one + middle + part_two

def render(page, dir):
    print("stat_cod: 200")
    with open(f"src/cgi/{dir}/{page}") as source:
        for line in source:
            if ('{{' in line and '}}' in line):
                line = insert_env(line)
            print(line)

def count_size(page, dir):
    all = 0
    body = ''
    with open(f"src/cgi/{dir}/{page}") as source:
        for line in source:
            if ('{{' in line and '}}' in line):
                line = insert_env(line)
            all += len(line.encode('utf-8'))
            body += line
    return all, body

def check_login():
    un = os.getenv("username", "")
    ps = os.getenv("password", "")
    if un == "username" and ps == "Mazen123":
        return True
    else:
        return False

if (sys.argv[2] != "GET"):
    data = ""
    data = sys.stdin.read()  # Odczyt całej zawartości ze stdin

try:
    qs = os.getenv("QUERY_STRING", "")
    parse_args(qs)
    if (sys.argv[2] != "GET"):
        parse_post_args(data)
    page = sys.argv[1].replace('.py', '.html')

    if page == 'bday_share.html':
        os.environ['shared_bd'] = find_party()
    access = True
    if "login" in page:
        access = check_login()
    html_pages = os.listdir(f'{os.getcwd()}/src/cgi/html')
    css_pages = os.listdir(f'{os.getcwd()}/src/cgi/style')

    if 'html' in page and page in html_pages and access:
        render(page, 'html')
    elif 'css' in page and page in css_pages:
        render(page, 'style')
    elif not access:
        print("stat_cod: 401")
    else:
        print("stat_cod: 404")
except:
    print("stat_cod: 500")
    
