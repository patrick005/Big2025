import sys
from selenium import webdriver
from selenium.webdriver.chrome.service import Service
from selenium.webdriver.common.by import By
from PySide6.QtWidgets import QApplication, QWidget, QGridLayout, QLabel
from PySide6.QtCore import Qt

def get_diet_menu_data(url="https://sejong.korea.ac.kr/koreaSejong/8028/subview.do", driver_path="chromedriver-linux64/chromedriver"):
    """웹 페이지에서 식단표 데이터를 추출합니다."""
    service = Service(executable_path=driver_path)
    options = webdriver.ChromeOptions()
    driver = webdriver.Chrome(service=service, options=options)

    try:
        driver.get(url)
        off_text_elements = driver.find_elements(By.CSS_SELECTOR, 'div.diet-menu p.offTxt')
        data = [element.text.strip() for element in off_text_elements]
        return data
    except Exception as e:
        print(f"데이터 추출 중 오류 발생: {e}")
        return []
    finally:
        driver.quit()

class DietMenuGUI(QWidget):
    def __init__(self, diet_data):
        super().__init__()
        self.setWindowTitle("오늘의 식단표")
        self.setGeometry(100, 100, 600, 600)

        layout = QGridLayout()

        if diet_data:
            row_count = 8
            col_count = 5
            data_index = 0

            for row in range(row_count):
                for col in range(col_count):
                    if data_index < len(diet_data):
                        label = QLabel(diet_data[data_index])
                        label.setAlignment(Qt.AlignCenter)
                        layout.addWidget(label, row, col)
                        data_index += 1
                    else:
                        empty_label = QLabel("")
                        layout.addWidget(empty_label, row, col)
        else:
            no_data_label = QLabel("식단표 데이터를 찾을 수 없습니다.")
            layout.addWidget(no_data_label, 0, 0, 1, 8)

        self.setLayout(layout)

def show_diet_menu_gui(diet_data):
    """추출된 식단표 데이터를 8x8 GUI로 표시합니다."""
    app = QApplication(sys.argv)
    gui = DietMenuGUI(diet_data)
    gui.show()
    sys.exit(app.exec())

if __name__ == "__main__":
    diet_data = get_diet_menu_data()
    if diet_data:
        show_diet_menu_gui(diet_data)
    else:
        print("표시할 식단표 데이터가 없습니다.")