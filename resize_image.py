from PIL import Image

path = input()
try:
    img = Image.open(path)
except:
    print("Can't open picture")
    exit(0)
save_path = input()
size_1 = int(input())
size_2 = int(input())

img.thumbnail((size_2, size_1))
img.save(save_path)