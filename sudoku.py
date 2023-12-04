import pygame, sys
from board import Board
from constants import Constants

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
            # Only cells that were not randomly generated can be edited/sketched/deleted. board.original_board is used
            # to check if the cell's original value is 0; if it is, the cell can be edited/sketched/deleted.

            # When a single digit integer is pressed, the corresponding value is sketched into the selected cell if that
            # cell's value currently equals 0 (the cell is visually empty on the board)
                if event.key == pygame.K_1:
                    if cell.value == 0:
                        board.sketch(1, row, col, cell)
                if event.key == pygame.K_2:
                    if cell.value == 0:
                        board.sketch(2, row, col, cell)
                if event.key == pygame.K_3:
                    if cell.value == 0:
                        board.sketch(3, row, col, cell)
                if event.key == pygame.K_4:
                    if cell.value == 0:
                        board.sketch(4, row, col, cell)
                if event.key == pygame.K_5:
                    if cell.value == 0:
                        board.sketch(5, row, col, cell)
                if event.key == pygame.K_6:
                    if cell.value == 0:
                        board.sketch(6, row, col, cell)
                if event.key == pygame.K_7:
                    if cell.value == 0:
                        board.sketch(7, row, col, cell)
                if event.key == pygame.K_8:
                    if cell.value == 0:
                        board.sketch(8, row, col, cell)
                if event.key == pygame.K_9:
                    if cell.value == 0:
                        board.sketch(9, row, col, cell)

                if event.key == pygame.K_BACKSPACE:
                    # Set the sketched value and cell value to 0 and re-draws the board to reflect these changes

                    # Only does so if the value was not randomly generated (not entered by user)
                    if board.original_board[row][col] == 0:
                        cell.set_sketched_value(0)
                        cell.set_cell_value(0)
                        screen.fill(Constants.BG_COLOR)
                        board.update_board()
                        board.draw()

                if event.key == pygame.K_RETURN:
                    # Sets the sketched value of the selected cell to the cell value and re-draws the updated board

                    # Only does so if the value was not randomly generated (not entered by user)
                    if board.original_board[row][col] == 0:
                        cell.set_cell_value(cell.sketched_value)
                        board.update_board()
                        screen.fill(Constants.BG_COLOR)
                        board.draw()
                    print(board.is_full())

                if event.key == pygame.K_DOWN and row != 8:
                    # when the down arrow key is pressed, the cell below the current cell will become selected/outlined
                    # Only does this if it is not the last row of the board
                    row += 1
                    screen.fill(Constants.BG_COLOR)
                    board.draw()
                    cell = board.select(row, col)

                if event.key == pygame.K_UP and row != 0:
                    # when the up arrow key is pressed, the cell above the current cell will become selected/outlined
                    # Only does this if it is not the first row of the board
                    row -= 1
                    screen.fill(Constants.BG_COLOR)
                    board.draw()
                    cell = board.select(row, col)

                if event.key == pygame.K_LEFT and col != 0:
                    # when left arrow key is pressed, the cell left of the current cell will become selected/outlined
                    # Only does this if it is not the first column of the board
                    col -= 1
                    screen.fill(Constants.BG_COLOR)
                    board.draw()
                    cell = board.select(row, col)

                if event.key == pygame.K_RIGHT and col != 8:
                    # when the right arrow key is pressed, the cell right of the current cell will become selected
                    # Only does this if it is not the last column of the board
                    col += 1
                    screen.fill(Constants.BG_COLOR)
                    board.draw()
                    cell = board.select(row, col)


        if event.type == pygame.KEYDOWN and cell is None:
            # when no cell is selected, pressing one of the arrow keys will select the top left cell
            if event.key == pygame.K_LEFT or event.key == pygame.K_RIGHT or event.key == pygame.K_DOWN or event.key == pygame.K_UP:
                row, col = 0, 0
                cell = board.select(row, col)


    pygame.display.update()

