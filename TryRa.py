from playwright.sync_api import sync_playwright, expect
import time
import pytest

playwright = sync_playwright().start()
browser = playwright.chromium.launch(headless=False)
page = browser.new_page()
page.goto("https://visa.vfsglobal.com/ind/en/deu/login")
time.sleep(5)
page.query_selector('xpath=//*[@id="mat-input-0"]').fill("ravi.has.kiran@gmail.com")
page.query_selector('xpath=//*[@id="mat-input-1"]').fill("Nokia$89")
page.query_selector('xpath=//html/body/app-root/div/app-login/section/div/div/mat-card/form/button/span[1]').click()
app_status = page.inner_text('xpath=//html/body/app-root/div/app-dashboard/section/div/div[2]/mat-tab-group/div/mat-tab-body/div/div')
#assert app_status == "No Application(s) Found."
if app_status == "No Application(s) Found.":
 print("yes")
time.sleep(10)
browser.close()
playwright.stop()


#/html/body/app-root/div/app-dashboard/section/div/div[2]/button/span[1] --> start booking 

#/html/body/app-root/div/app-dashboard/section/div/div[2]/mat-tab-group/div/mat-tab-body/div/div -->  No application(s) Found.

#page.goto("https://visa.vfsglobal.com/ind/en/deu/dashboard")

#https://stackoverflow.com/questions/49879993/push-notification-from-python-to-android --> notify run

#/html/body/app-root/div/app-dashboard/section/div/div[2]/mat-tab-group/div/mat-tab-body/div/div/div/div[2]/div[1] --> Group Reference Number - GEB6707934723

#/html/body/app-root/div/app-dashboard/section/div/div[2]/mat-tab-group/div/mat-tab-body/div/div/div/div[2]/div[2]/span --> Manage Application

#/html/body/app-root/div/app-dashboard/section/div/div[2]/mat-tab-group/div/mat-tab-body/div/div/div/div[3]/div --> Waitlist Status: WAITLISTED

#/html/body/app-root/div/app-dashboard/section/div/div[2]/mat-tab-group/div/mat-tab-body/div/div/div/div[4] --> Applicants:

#/html/body/app-root/div/app-dashboard/section/div/div[2]/mat-tab-group/div/mat-tab-body/div/div/div/div[5]/div --> SINDHU TELIKAPALLI
