from PIL import Image

path = input()
try:
    img = Image.open(path)
except:
    print("Can't open picture")
    exit(0)
save_path = input()
size = int(input())

img.thumbnail((size, size))
img.save(save_path)