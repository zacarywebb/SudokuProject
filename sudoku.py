import pygame, sys
from Projects.SudokuProject.board import Board
from Projects.SudokuProject.constants import Constants
from Projects.SudokuProject.sudoku_generator import SudokuGenerator
from Projects.SudokuProject.cell import Cell

def generate_sudoku(size, removed):
    sudoku = SudokuGenerator(size, removed)
    sudoku.fill_values()
    board = sudoku.get_board()
    sudoku.remove_cells()
    board = sudoku.get_board()
    sudoku.print_board()
    return board


pygame.init()
screen = pygame.display.set_mode((Constants.SCREEN_WIDTH, Constants.SCREEN_HEIGHT))
screen.fill(Constants.BG_COLOR)

board = Board(Constants.WIDTH, Constants.HEIGHT, screen, 30)
cell1 = Cell('3', 0, 0, screen)
board.draw()

while True:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            sys.exit()
    pygame.display.update()

