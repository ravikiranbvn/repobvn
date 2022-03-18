from playwright.sync_api import sync_playwright, expect
import time

playwright = sync_playwright().start()
browser = playwright.chromium.launch(headless=False)
page = browser.new_page()
page.goto("https://visa.vfsglobal.com/ind/en/deu/login")
time.sleep(3)
page.query_selector('xpath=//*[@id="mat-input-0"]').fill("sindhusruthi95@gmail.com")
page.query_selector('xpath=//*[@id="mat-input-1"]').fill("Ramachandra12*")
page.query_selector('xpath=//html/body/app-root/div/app-login/section/div/div/mat-card/form/button/span[1]').click()
time.sleep(50)
browser.close()
playwright.stop()
