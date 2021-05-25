
	
from tkinter import *
 
from tkinter.ttk import *
 
window = Tk()
 
window.title("Welcome to LikeGeeks app")
 
window.geometry('350x200')
 
combo = Combobox(window)
 
combo['values']= ('a','b')
 
combo.current(1) #set the selected item
 
combo.grid(column=0, row=0)
 
window.mainloop()
