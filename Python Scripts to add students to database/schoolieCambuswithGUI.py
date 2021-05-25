import tkinter as tk
from tkinter import *
from tkinter.ttk import *

#this function is used to open the addition tab
def addProgram():
    add=tk.Tk()
    add.title("Addition of Students")
    add.configure(background='#45adf7')
    add.geometry("220x150")
    add.resizable(0,0)
    #name
    namelabel=tk.Label(add,text="Name:",background='#45adf7',font=("Areal Bold",10))
    namelabel.grid(column=0,row=0)
    name=Entry(add,width=20)
    name.grid(column=1,row=0)
    #usn
    usnlabel=tk.Label(add,text="USN:",background='#45adf7',font=("Areal Bold",10))
    usnlabel.grid(column=0,row=1)
    usn=Entry(add,width=20)
    usn.grid(column=1,row=1)
    #busno
    buslabel=tk.Label(add,text="Bus no:",background='#45adf7',font=("Areal Bold",10))
    buslabel.grid(column=0,row=2)
    busno=Entry(add,width=20)
    busno.grid(column=1,row=2)
    #submit button
    submit=Button(add,text="Submit",command=Submit)
    submit.grid(column=1,row=3)
    add.mainloop()
def Submit():
    
    pass
def checkRfid():
    pass
#mainloop
win=tk.Tk()
win.resizable(0,0)
win.title("SchoolieCambus")
win.geometry("488x500")
win.configure(background='#45adf7')
#head
headTitle=tk.Label(win,text="www.SchoolieCambus.com",font=("Areal Bold",30))
headTitle.configure(background='red')
headTitle.grid(column=0,row=0)
#credit
credit=tk.Label(win,text="A project by Vinay SV and ASV.")
credit.configure(background='red')
credit.grid(column=0,row=9)
#choose option
funTitle=tk.Label(win,text="select an option:",font=("Areal Bold",10),background='#45adf7')
funTitle.grid()
#choose COM port to open
selcomport=Combobox(win)
selcomport['values']=('COM0','COM1','COM2','COM3','COM4','COM5','COM6','COM7','COM8','COM9','COM10','COM11','COM12','COM13','COM14','COM15','COM16','COM17','COM18','COM19','COM20','COM21','COM22','COM23','COM24','COM25','COM26','COM27','COM28','COM29','COM30')
selcomport.current(10)
selcomport.grid(column=0,row=30)
#addition tab button
addBtn=Button(win,text="Addition of Students",command=addProgram)
addBtn.grid(column=0,row=50)
#end of the main loop
win.mainloop()


