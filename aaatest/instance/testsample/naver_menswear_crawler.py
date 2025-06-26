import os
import time
import requests
from PIL import Image
from io import BytesIO
from urllib.parse import quote

from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.chrome.options import Options
from selenium.webdriver.chrome.service import Service
from webdriver_manager.chrome import ChromeDriverManager

# 설정
BASE_DIR = "/home/aa/Big2025/aaatest/instance/testsample"
categories = ["셔츠", "반팔티", "맨투맨", "후드티", "니트", "자켓"]

def get_driver():
    options = Options()
    options.add_argument("--headless=new")  # JS 렌더링 + headless
    options.add_argument("--disable-gpu")
    options.add_argument("--no-sandbox")
    options.add_argument("--disable-dev-shm-usage")
    options.add_argument("--window-size=1920x1080")
    options.add_argument("--disable-blink-features=AutomationControlled")
    options.add_argument(
        "user-agent=Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/122.0.0.0 Safari/537.36"
    )
    return webdriver.Chrome(service=Service(ChromeDriverManager().install()), options=options)

def save_image(url, save_dir, prefix):
    try:
        res = requests.get(url, timeout=5)
        img = Image.open(BytesIO(res.content)).convert("RGB")
        filename = f"{prefix}_{int(time.time() * 1000)}.jpg"
        img.save(os.path.join(save_dir, filename), format="JPEG")
    except Exception as e:
        print(f"[실패] 이미지 저장 오류: {e}")

def crawl_coupang(driver, keyword, max_count=50):
    encoded = quote(keyword)
    url = f"https://www.coupang.com/np/search?q={encoded}&channel=user"

    driver.get(url)
    time.sleep(4)  # JS 렌더링 대기

    # 이미지 태그 수집
    img_elements = driver.find_elements(By.CSS_SELECTOR, "img.search-product-wrap-img")
    print(f"[{keyword}] 이미지 {len(img_elements)}개 감지됨")

    save_dir = os.path.join(BASE_DIR, "쿠팡_" + keyword)
    os.makedirs(save_dir, exist_ok=True)

    count = 0
    for img in img_elements:
        if count >= max_count:
            break
        src = img.get_attribute("src")
        if src and "data:image" not in src:
            save_image(src, save_dir, prefix="img")
            count += 1
            time.sleep(0.2)
    print(f"[완료] {keyword}: {count}장 저장됨")

if __name__ == "__main__":
    driver = get_driver()
    try:
        for cat in categories:
            crawl_coupang(driver, cat, max_count=50)
    finally:
        driver.quit()
