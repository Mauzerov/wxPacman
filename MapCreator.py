import tkinter as tk
x = int(input("Rozmiar X: "))
y = int(input("Rozmiar Y: "))
if x <=0 or y <=0 or y >35 or x > 70:
	raise ValueError
	
columns = [[]]*y
enabled = [[]]*y
root = tk.Tk()
root.title("Map Creator")
frame = tk.Frame(root,bg="#000")
frame.pack()

def change(column,row):
	if enabled[row][column]:
		columns[row][column].configure(bg="#000",fg="#fff")
		enabled[row][column] = not enabled[row][column]
	else:
		columns[row][column].configure(bg="#fff",fg="#000")
		enabled[row][column] = not enabled[row][column]
def click(event): 
	posx = event.x_root - frame.winfo_rootx() 
	posy = event.y_root - frame.winfo_rooty() 
	z = frame.grid_location(posx, posy)
	if z[1] < y:
		change(z[0],z[1])
def zapisz_do_pliku(puste,mur,nazwa):
	try:
		with open(nazwa+".txt","w") as m:
			m.write("")
		with open(nazwa+".txt","a+") as mapa:
			for i in range(y):
				for j in range(x):
					if enabled[i][j]: mapa.write(str(puste)+" ")
					else: mapa.write(str(mur)+" ")
				mapa.write("\n")
	except Exception as e:
		raise e
def save():
	PUSTE = pusteEntry.get()
	MUR = murEntry.get()
	nazwa =  nazwaEntry.get()
	try:
		PUSTE = int(PUSTE)
		MUR = int(MUR)
	except Exception:
		return
	if nazwa != "":
		zapisz_do_pliku(PUSTE,MUR,nazwa)

# Main()
for i in range(y):
	buttons,preE = [],[]
	for j in range(x):
		preE.append(False)
		buttons.append(tk.Button(frame,text=j+1,width=2,height=1,bg="#000",fg="#fff"))
		buttons[j].grid(row=i,column=j)
	columns[i] = buttons
	enabled[i] = preE
## Bottom
nazwaEntry = tk.Entry(frame,bg="#000",fg="#fff",insertbackground="#fff")
nazwaEntry.grid(row=y,column=5,columnspan=5)
nazwaLabel = tk.Label(frame,bg="#000",fg="#fff",text="File Name (no file type): ")
nazwaLabel.grid(row=y,column=0,columnspan=5)

pusteEntry = tk.Entry(frame,bg="#000",fg="#fff",insertbackground="#fff")
pusteEntry.grid(row=y,column=15,columnspan=5)
pusteLabel = tk.Label(frame,bg="#000",fg="#fff",text="Empty Square Value: ")
pusteLabel.grid(row=y,column=10,columnspan=5)

murEntry = tk.Entry(frame,bg="#000",fg="#fff",insertbackground="#fff")
murEntry.grid(row=y,column=25,columnspan=5)
murLabel = tk.Label(frame,bg="#000",fg="#fff",text="Wall Value: ")
murLabel.grid(row=y,column=20,columnspan=5)

zapiszButton = tk.Button(frame,bg="#000",fg="#fff",text="Save",width=10,command=save)
zapiszButton.grid(row=y,column=30,columnspan=5)

infoLabel = tk.Label(frame,bg="#000",fg="#fff",text="Black = WALL\t:\tWHITE = EMPTY")
infoLabel.grid(row=y,column=35,columnspan=15)

root.bind("<Button-1>",click)
root.mainloop()
