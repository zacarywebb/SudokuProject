import pygame
from Projects.SudokuProject.constants import *


class Board:
    def __init__(self, width, height, screen, difficulty):
        self.width = width
        self.height = height
        self.screen = screen
        self.difficulty = difficulty

    def draw(self):
        # Draw horizontal lines
        for i in range(Constants.BOARD_LINES):
            pygame.draw.line(
                self.screen,
                Constants.LINE_COLOR,
                (147, i * Constants.BOX_SIZE + 150),
                (Constants.SCREEN_WIDTH - 150, i * Constants.BOX_SIZE + 150),
                Constants.LINE_WIDTH
            )

        # Draw vertical lines
        for i in range(Constants.BOARD_LINES):
            pygame.draw.line(
                self.screen,
                Constants.LINE_COLOR,
                (i * Constants.BOX_SIZE + 150, 146),
                (i * Constants.BOX_SIZE + 150, Constants.HEIGHT + 155),
                Constants.LINE_WIDTH
            )

        # NEED TO DRAW EACH CELL HERE



