#!/usr/bin/python
from playwright.sync_api import sync_playwright, expect
import time
import json
import requests
import http.client as httplib

#webhook url on slack app -> ServiceTrainToRaviSindhu
webhook_url = "https://hooks.slack.com/services/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"

#start playwright -> with chromium in icognitive window
playwright = sync_playwright().start()
browser = playwright.chromium.launch(headless=False)
page = browser.new_page()

#check for internet
def func_have_internet():
    conn = httplib.HTTPSConnection("8.8.8.8", timeout=5)
    try:
        conn.request("HEAD", "/")
        return True
    except Exception:
        return False
    finally:
        conn.close()

#on page-> https://visa.vfsglobal.com/ind/en/deu/login
def func_login(page):
 page.goto("https://visa.vfsglobal.com/ind/en/deu/login")
 time.sleep(5)
 page.query_selector('xpath=//*[@id="mat-input-0"]').fill("sindhusruthi95@gmail.com")
 page.query_selector('xpath=//*[@id="mat-input-1"]').fill("Ramachandra12*")
 page.query_selector('xpath=//html/body/app-root/div/app-login/section/div/div/mat-card/form/button/span[1]').click()

#On page-> https://visa.vfsglobal.com/ind/en/deu/dashboard
def func_check1(page):
 reference_no = page.inner_text('xpath=//html/body/app-root/div/app-dashboard/section/div/div[2]/mat-tab-group/div/mat-tab-body/div/div/div/div[2]/div[1]')
 #check for reference no
 if reference_no == "Group Reference Number - GEB6707934723":
  return True
 else:
  return False
 
def func_check2(page):
 manage_app = page.inner_text('xpath=//html/body/app-root/div/app-dashboard/section/div/div[2]/mat-tab-group/div/mat-tab-body/div/div/div/ div[2]/div[2]/span')
 #check for manage application
 if manage_app == "Manage Application":
  return True
 else:
  return False

def func_check3(page):
 waitlist_status = page.inner_text('xpath=//html/body/app-root/div/app-dashboard/section/div/div[2]/mat-tab-group/div/mat-tab-body/div/    div/div/div[3]/div')
 #check for waitlist status
 if waitlist_status == "Waitlist Status: WAITLISTED":
  return True
 else:
  return False

def func_check4(page):
 applicant_name = page.inner_text('xpath=//html/body/app-root/div/app-dashboard/section/div/div[2]/mat-tab-group/div/mat-tab-body/div/div/div/div[5]/div')
 #check for applicant name
 if applicant_name == "SINDHU TELIKAPALLI":
  return True
 else:
  return False

def func_signout(page):
 page.query_selector('xpath=//html/body/app-root/header/div/div/div/ul/li/a').click()

def main():
 if func_have_internet() == True:
   func_login(page)
   
 if func_check1(page) == True:
  if func_check2(page) == True:
   if func_check3(page) == True:
    if func_check4(page) == True:
     slack_data = {'text': "All tests passed!"}
     response = requests.post(webhook_url, data=json.dumps(slack_data),
     headers={'Content-Type': 'application/json'})
     
     if response.status_code != 200:
      raise ValueError(
      'Request to slack returned an error %s, the response is:\n%s' % (response.status_code, response.text))
 
 time.sleep(5)       
 func_signout(page)
 time.sleep(5)
 browser.close()
 playwright.stop()

if __name__ == "__main__":
    main()






        
