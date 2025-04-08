import requests
import webbrowser


url = input()

result = requests.get(url)

print(result.text)

if (result.status_code == 200):
    print("Success")

    file_path = "output.html"

    html_content = result.text

    with open(file_path, "w", encoding="utf-8") as file:
        file.write(html_content)

    print(f"HTML 文件已保存为: {file_path}")


    webbrowser.open(file_path)