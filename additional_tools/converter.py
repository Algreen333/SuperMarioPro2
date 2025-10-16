import cv2
import string
import random

colors = {'0x000000': '_', '0xFFFFFF': 'w'}

def bgr_to_hex(bgr):
    b, g, r = bgr
    return '0x{:02X}{:02X}{:02X}'.format(r, g, b)

def rand_string(length=2):
    chars = string.ascii_letters  # a-zA-Z0-9
    return ''.join(random.choice(chars) for _ in range(length))

def get_bitmap(char):
    global colors

    h, w, _ = char.shape
    
    result = []

    for y in range(9):
        line = []
        for x in range(5):
            px = bgr_to_hex(char[y*8, x*8])
            if px not in colors.keys():
                colors[px] = rand_string()
            line.append(colors[px])
        result.append(line)
    
    return result

def save_chars(chars):
    print(chars)
    text = f"{len(chars)} {len(chars[0])} {len(chars[0][0])}\n\n"
    for i in range(len(chars)):
        char = chars[i]
        for y in range(len(char)):
            for x in range(len(char[y])):
                text+=char[y][x]
                if x < len(char[y]) - 1: text+=" "
            text+="\n"
        text+="\n"

    path = input("Save charset as: ")

    with open(path, "w") as f:
        f.write(text)

def save_colors(colors):
    text = ""
    for color in colors.keys():
        text += colors[color] + " " + color + " "
    text += '\n'

    path = input("Save colors as: ")
    with open(path, "w") as f:
        f.write(text)


if __name__ == "__main__":
    file = input("Fitxer Bitmap? ")
    im = cv2.imread(file)

    h, w, _ = im.shape

    names = string.ascii_uppercase + string.ascii_lowercase + string.digits + f"+-=()[]{'{'}{'}'}<>/*:#%!?.,'{'"'}@&$ "
    print(names, '\n')


    offset_x = input("Offset en x dels caràcters? ")
    offset_y = input("Offset en y dels caràcters? ")

    num_total = input("\nNombre total de caràcters? ")
    num_cols = input("Nombre de columnes? ")

    w_char = input("Amplada dels caràcters? ")
    h_char = input("Alçada dels caràcters? ")

    sep_x = input("Espai en x entre caràcters? ")
    sep_y = input("Espai en y entre caràcters? ")
    
    chars = []
    
    for x in range(num_total):
        chars.append(
            im[offset_y+(offset_y*int(x/num_cols)) : offset_y + h_char +((h_char + sep_y)*int(x/num_cols)), 
               offset_x +(w_char*x%num_cols) : offset_x + w_char +((w_char + sep_x)*int(x/num_cols))])
        

    for j in range(6):
        for i in range(13):
            chars.append(im[48+(80*j) : 120+(80*j) , 48+(48*i) : 88+(48*i)])

    j = 6
    for i in range(10):
            chars.append(im[48+(80*j) : 120+(80*j) , 48+(48*i) : 88+(48*i)])

    bmaps = []
    for i in range(len(chars)):
        bmaps.append(get_bitmap(chars[i]))
    save_chars(bmaps)

    if ("y" in input("Save colors? (y/n)").lower()): save_colors(colors)