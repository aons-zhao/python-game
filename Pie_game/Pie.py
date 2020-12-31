import pygame
from pygame.locals import *

pygame.init()
screen = pygame.display.set_mode((600, 500))  # 创建一个600*500的窗口

white = 255, 255, 255
blue = 0, 0, 255

myfont = pygame.font.Font(None, 60)  # 创建一个字体对象，None默认为pygame的字体
textImage = myfont.render("hello Pygame", True, white)

screen.fill(blue)
screen.blit(textImage, (100, 100))
pygame.display.update()