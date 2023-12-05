import pygame
from Projects.SudokuProject.constants import *
class Cell:
    def __init__(self, value, row, col, screen):
        self.value = value
        self.row = row
        self.col = col
        self.screen = screen
        self.cell_font = pygame.font.Font(None, 50)
        self.name = ""
        self.sketched_value = 0
        self.original_value = self.value

    def set_cell_value(self, value):
        self.value = value

    def set_sketched_value(self, value):
        self.sketched_value = value

    def draw(self):
        # If the cell's original value is 0, when printing, the cell's font color should be blue
        if self.original_value == 0:
            cell_font_surf = self.cell_font.render(str(self.value), 0, (0, 100, 150))
        else:
            cell_font_surf = self.cell_font.render(str(self.value), 0, (0, 0, 0))

        # Print the cell value in the correct location if the value is not 0
        if self.value != 0:
            cell_rect = cell_font_surf.get_rect(center = (150 + Constants.CELL_SIZE/2 + self.col * Constants.CELL_SIZE, 150 + Constants.CELL_SIZE/2 + self.row * Constants.CELL_SIZE))
            self.screen.blit(cell_font_surf, cell_rect)

            # If the cell has a sketched value, it should be printed
        elif self.sketched_value != 0:
            sketched_cell_font = pygame.font.Font(None, 35)
            sketched_cell_font_surf = sketched_cell_font.render(str(self.sketched_value), 0, (128, 128, 160))
            sketched_cell_rect = sketched_cell_font_surf.get_rect(center=(163 + self.col * Constants.CELL_SIZE, 170 + self.row * Constants.CELL_SIZE))
            self.screen.blit(sketched_cell_font_surf, sketched_cell_rect)

        # Draw the outline of the cell
        pygame.draw.line(
            self.screen,
            Constants.LINE_COLOR,
            (150 + self.col * Constants.CELL_SIZE, 150 + (self.row + 1) * Constants.CELL_SIZE),
            (150 + (self.col) * Constants.CELL_SIZE + Constants.CELL_SIZE, 150 + (self.row + 1) * Constants.CELL_SIZE),
            Constants.CELL_LINE_WIDTH

        )

        pygame.draw.line(
            self.screen,
            Constants.LINE_COLOR,
            (150 + (self.col + 1) * Constants.CELL_SIZE, 150 + self.row * Constants.CELL_SIZE),
            (150 + (self.col + 1) * Constants.CELL_SIZE, 150 + self.row * Constants.CELL_SIZE + Constants.CELL_SIZE),
            Constants.CELL_LINE_WIDTH

        )