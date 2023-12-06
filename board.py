import pygame
from constants import *
from cell import Cell
from sudoku_generator import SudokuGenerator
from button import Button
import sys
pygame.init()


class Board:
    def __init__(self, width, height, screen, difficulty):
        self.width = width
        self.height = height
        self.screen = screen
        self.difficulty = difficulty
        self.cell_dict = {}

        # Create an instance of SudokuGenerator class and assign self.correct_board with a 2D list that has no
        # removed values. Uses a copy so editing self.board does not edit self.correct_board
        sudoku = SudokuGenerator(9, difficulty)
        sudoku.fill_values()
        correct_board_copy = sudoku.get_board()
        self.correct_board = [x[:] for x in correct_board_copy]

        # Remove cells from the 2D list, replacing them with zeroes. Initialize self.board to equal this 2D list
        sudoku.remove_cells()
        board = sudoku.get_board()
        self.board = board

        # Create a copy of the original, unedited board so that the user may reset the board at any time
        self.original_board = [x[:] for x in self.board]


        # Create each cell
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

        exitbt = Button("Exit", 600, 800, True, self.screen)

        resetbt = Button("Reset", 200, 800, True, self.screen)
        restartbt = Button("Restart", 400, 800, True, self.screen)
        lose = Button("lose", 800, 800, True, self.screen)




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
        # Updates self.board to reflect any changes to cell values
        for i in range(9):
            for j in range(9):
                self.board[i][j] = self.cell_dict[f'Cell{i}, {j}'].value


    def sketch(self, value, row, col, cell):
        # Sketches the user-entered value at the row and column of the selected cell
        # Also sets the cell's sketched value to the user entered value
        cell_font = pygame.font.Font(None, 35)
        cell_font_surf = cell_font.render(str(value), 0, (128, 128, 160))
        cell_rect = cell_font_surf.get_rect(center=(163 + col * Constants.CELL_SIZE, 170 + row * Constants.CELL_SIZE))
        cell.set_sketched_value(value)
        self.screen.blit(cell_font_surf, cell_rect)

    def is_full(self):
        # determines whether the board is full or not
        # checks if any part of the cell is not equal to 0

        for eachCell in self.board:
            for i in eachCell:
                if i == 0:
                    return False
        return True

    def reset_to_original(self):
        # Create a copy of the original board and set self.board equal to it
        self.board = [x[:] for x in self.original_board]

        # Reset Cell dictionary
        for i in range(9):
            for j in range(9):
                cell = Cell(self.board[i][j], i, j, self.screen)
                cell.name = f'Cell{i}, {j}'
                self.cell_dict[cell.name] = cell


    def check_board(self):
        # Returns True if every value in self.board equals the corresponding value in self.correct_board
        for i in range(9):
            for j in range(9):
                if self.board[i][j] != self.correct_board[i][j]:
                    return False

        return True
