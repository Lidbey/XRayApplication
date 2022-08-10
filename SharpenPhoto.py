from skimage.filters import unsharp_mask
import sys
from skimage import io

imgPath = sys.argv[1]
img = io.imread(sys.argv[1])
newImg = unsharp_mask(img, 5, 2)

io.imsave('./PythonImage.jpg', newImg)