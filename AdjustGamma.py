from skimage.exposure import adjust_gamma
import sys
from skimage import io

imgPath = sys.argv[1]
img = io.imread(sys.argv[1])
newImg = adjust_gamma(img, 3, 2)

io.imsave('./PythonImage.jpg', newImg)