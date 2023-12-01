import pygame
from Projects.SudokuProject.constants import *
class Cell:
    def __init__(self, value, row, col, screen):
        self.value = value
        self.row = row
        self.col = col
        self.screen = screen
        self.cell_font = pygame.font.Font(None, 50)

    def set_cell_value(self, value):
        pass

    def set_sketched_value(self, value):
        pass

    def draw(self):
        cell_font_surf = self.cell_font.render(self.value, 0, (0, 0, 0))
        cell_rect = cell_font_surf.get_rect(center = (150 + Constants.CELL_SIZE/2 + self.col * Constants.CELL_SIZE, 150 + Constants.CELL_SIZE/2 + self.row * Constants.CELL_SIZE))
        self.screen.blit(cell_font_surf, cell_rect)