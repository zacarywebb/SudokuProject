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

        if event.type == pygame.KEYDOWN:
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

            if event.key == pygame.K_RETURN:
                # Sets the sketched value of the selected cell to the cell value
                cell.set_cell_value(cell.sketched_value)
                screen.fill(Constants.BG_COLOR)
                board.update_board()
                board.draw()
    pygame.display.update()

