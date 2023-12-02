import pygame, sys
from Projects.SudokuProject.board import Board
from Projects.SudokuProject.constants import Constants

# Initialize pygame and the screen
pygame.init()
screen = pygame.display.set_mode((Constants.SCREEN_WIDTH, Constants.SCREEN_HEIGHT))
screen.fill(Constants.BG_COLOR)

# Initialize the board and draw it
board = Board(Constants.WIDTH, Constants.HEIGHT, screen, 30)
board.draw()


no_winner = True
cell = None

while no_winner:
    for event in pygame.event.get():
        # Quit program if the user closes the window
        if event.type == pygame.QUIT:
            pygame.quit()
            sys.exit()

        # If the user clicks down on the mouse pad
        if event.type == pygame.MOUSEBUTTONDOWN:
            x, y = event.pos
            if board.click(x, y) is not None:
                # Reset the board to remove a previous cell selection (removes the red outline)
                screen.fill(Constants.BG_COLOR)
                board.draw()
                row, col = board.click(x, y)
                cell = board.select(row, col)

        if event.type == pygame.KEYDOWN and cell is not None:
            if event.key == pygame.K_1:
                board.sketch(1, row, col, cell)
            if event.key == pygame.K_2:
                board.sketch(2, row, col, cell)
            if event.key == pygame.K_3:
                board.sketch(3, row, col, cell)
            if event.key == pygame.K_4:
                board.sketch(4, row, col, cell)
            if event.key == pygame.K_5:
                board.sketch(5, row, col, cell)
            if event.key == pygame.K_6:
                board.sketch(6, row, col, cell)
            if event.key == pygame.K_7:
                board.sketch(7, row, col, cell)
            if event.key == pygame.K_8:
                board.sketch(8, row, col, cell)
            if event.key == pygame.K_9:
                board.sketch(9, row, col, cell)

            if event.key == pygame.K_BACKSPACE:
                # Set the sketched value and cell value to 0 and redraw the board to reflect these changes
                cell.set_sketched_value(0)
                cell.set_cell_value(0)
                screen.fill(Constants.BG_COLOR)
                board.update_board()
                board.draw()

            if event.key == pygame.K_RETURN:
                # Sets the sketched value of the selected cell to the cell value and redraws the updated board
                cell.set_cell_value(cell.sketched_value)
                board.update_board()
                screen.fill(Constants.BG_COLOR)
                board.draw()
    pygame.display.update()

