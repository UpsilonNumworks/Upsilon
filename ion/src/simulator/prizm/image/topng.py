# Convert the raw 320 * 240 RGB565 data in test.bin to a PNG image

from PIL import Image

# Open the raw data file
with open('test.bin', 'rb') as f:
    # Read the raw data
    data = f.read()

# Create a new image
img = Image.new('RGB', (320, 240))

# Convert the raw data to RGB565 and save it to the image
for y in range(240):
    for x in range(320):
        # Read 2 bytes from the raw data
        b = data[(y * 320 + x) * 2 : (y * 320 + x) * 2 + 2]
        # Convert the 2 bytes to an integer
        i = int.from_bytes(b, 'little')
        # Convert the RGB565 to RGB888
        r = ((i >> 11) & 0x1F) << 3
        g = ((i >> 5) & 0x3F) << 2
        b = (i & 0x1F) << 3
        # Save the RGB888 to the image
        img.putpixel((x, y), (r, g, b))

# Save the image to a PNG file
img.save('test.png')
