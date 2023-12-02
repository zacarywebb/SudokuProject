import pygame
from Projects.SudokuProject.constants import *
from cell import Cell
from sudoku_generator import generate_sudoku

class Board:
    def __init__(self, width, height, screen, difficulty):
        self.width = width
        self.height = height
        self.screen = screen
        self.difficulty = difficulty
        self.cell_dict = {}
        # Create each cell
        self.board = generate_sudoku(9, self.difficulty)
        for i in range(9):
            for j in range(9):
                cell = Cell(self.board[i][j], i, j, self.screen)
                cell.name = f'Cell{i}, {j}'
                self.cell_dict[cell.name] = cell

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
                (i * Constants.BOX_SIZE + 150, 147),
                (i * Constants.BOX_SIZE + 150, Constants.HEIGHT + 153),
                Constants.LINE_WIDTH
            )

        for i in range(9):
            for j in range(9):
                cell = self.cell_dict[f'Cell{i}, {j}']
                cell.draw()

    def click(self, x, y):
        # Returns a tuple (row, col) of the cell that was marked at location (x, y)
        row = -1
        col = -1
        if (150 <= x <= 750) and (150 <= y <= 750):
            for i in range(9):
                if (150 + (i * Constants.CELL_SIZE)) <= float(x) <= (150 + (i * Constants.CELL_SIZE) + Constants.CELL_SIZE):
                    col = i
                    break

            for j in range(9):
                if (150 + (j * Constants.CELL_SIZE)) <= float(y) <= (150 + (j * Constants.CELL_SIZE) + Constants.CELL_SIZE):
                    row = j
                    break

            return row, col

    def select(self, row, col):
        cell = self.cell_dict[f'Cell{row}, {col}']
        pygame.draw.rect(self.screen, Constants.SELECTED_LINE_COLOR, (151 + col * Constants.CELL_SIZE, 150 + row *
                                                                      Constants.CELL_SIZE, Constants.CELL_SIZE + 1, Constants.CELL_SIZE + 2), 4)
        return cell

    def update_board(self):
        for i in range(9):
            for j in range(9):
                self.board[i][j] = self.cell_dict[f'Cell{i}, {j}'].value


    def sketch(self, value, row, col, cell):
        cell_font = pygame.font.Font(None, 35)
        cell_font_surf = cell_font.render(str(value), 0, (128, 128, 160))
        cell_rect = cell_font_surf.get_rect(center=(163 + col * Constants.CELL_SIZE, 170 + row * Constants.CELL_SIZE))
        cell.set_sketched_value(value)
        self.screen.blit(cell_font_surf, cell_rect)
