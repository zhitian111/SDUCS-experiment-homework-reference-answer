import tkinter as tk
import numpy as np
from tkinter import ttk
import os

ROWS = 8
COLS = 8
MODOLE_SIZE = 10
filename = f"numbers{ROWS}x{COLS}.npy"
CELL_SIZE = 50

draw_btns = [[None for _ in range(COLS)] for _ in range(ROWS)]
sel_combo = None
refresh_btn = None
save_btn = None
exit_btn = None
shift_on = False
lastbutton = [0, 0]
reset_btn = None

all_list = np.zeros((MODOLE_SIZE, ROWS * COLS))
if filename in os.listdir():
    all_list = np.load(filename)
else:
    all_list.fill(-1)

root = tk.Tk()
root.title("数字绘制")


def refresh():
    for i in range(ROWS):
        for j in range(COLS):
            if all_list[sel_combo.current()][i * COLS + j] == -1:
                draw_btns[i][j].config(bg="white")
            else:
                draw_btns[i][j].config(bg="black")


def draw(i, j):
    global lastbutton
    sel_cur = sel_combo.current()
    if shift_on:
        for r in range(lastbutton[0], i + 1):
            for c in range(lastbutton[1], j + 1):
                all_list[sel_cur][r * COLS + c] = -1 if all_list[sel_cur][r * COLS + c] == 1 else 1
        all_list[sel_cur][lastbutton[0] * COLS + lastbutton[1]] = -1 if all_list[sel_cur][lastbutton[0] * COLS +
                                                                                          lastbutton[1]] == 1 else 1
    else:
        all_list[sel_cur][i * COLS + j] = -1 if all_list[sel_cur][i * COLS + j] == 1 else 1
        lastbutton = [i, j]
    refresh()


def on_select(event):
    refresh()


def on_shift(event):
    global shift_on
    shift_on = False if shift_on else True
    print(shift_on)

def reset():
    all_list[sel_combo.current()].fill(-1)
    refresh()

for i in range(ROWS):
    for j in range(COLS):
        btn = tk.Button(root, text="", width=6, height=2,
                        command=lambda ii=i, jj=j: draw(ii, jj))
        btn.grid(row=i, column=j)
        draw_btns[i][j] = btn

options = [str(i) for i in range(10)]
sel_combo = ttk.Combobox(root, values=options, state="readonly")
sel_combo.current(0)
sel_combo.grid(row=0, column=COLS)
sel_combo.bind("<<ComboboxSelected>>", on_select)

refresh_btn = tk.Button(root, text="刷新", command=refresh)
refresh_btn.grid(row=ROWS, column=0)

reset_btn = tk.Button(root, text="重置", command=reset)
reset_btn.grid(row=ROWS, column=1)

save_btn = tk.Button(root, text="保存", command=lambda: np.save(filename, all_list))
save_btn.grid(row=ROWS, column=2)

exit_btn = tk.Button(root, text="退出", command=root.quit)
exit_btn.grid(row=ROWS, column=COLS - 1)



root.bind_all("<KeyPress-Shift_L>", on_shift)

refresh()
root.mainloop()
