import pygame, sys
from board import Board
from constants import Constants

# Initialize pygame and the screen
pygame.init()
screen = pygame.display.set_mode((Constants.SCREEN_WIDTH, Constants.SCREEN_HEIGHT))
screen.fill(Constants.BG_COLOR)

difficulty = None
# ADD MENU SCREEN AND BOTTON CODE
# Initialize the board and draw it
pygame.display.set_caption("Sudoku")

# Assign font's for texts
font = pygame.font.SysFont("arialblack", 75)
button_font = pygame.font.SysFont("arialblack", 50)

# Assign dimensions for button's to select difficulty
easy_button_rect = pygame.Rect(100, 600, 150, 50)
medium_button_rect = pygame.Rect(325, 600, 200, 50)
hard_button_rect = pygame.Rect(650, 600, 150, 50)

# Assigns text colors
TEXT_COL = (0, 0, 0) # Normal Text color
EASY_HIGHTLIGHT_COLOR = (50, 205, 50) # Green Highlight
MEDIUM_HIGHTLIGHT_COLOR = (255, 165, 0) # Orange Highlight
HARD_HIGHTLIGHT_COLOR = (255, 0, 0) # Red Hightlight

def draw_text(text, font, text_col, x, y): # Renders text
    img = font.render(text, True, text_col)
    rect = img.get_rect(topleft=(x, y))
    screen.blit(img, rect)
    return rect

sudoku_headline = draw_text("SUDOKU!", font, TEXT_COL, 250, 250) # sudoku headline
select_game_mode = draw_text("Select Game Mode:", button_font, TEXT_COL, 175, 425) # select game mode headline

# boolean variables to track when main menu buttons are clicked
easy_button_clicked = False
medium_button_clicked = False
hard_button_clicked = False

# The game/board will not initialize until a difficulty has been chosen by the user
if difficulty is not None:
    cell = None
    # Initialize the board and draw it
    board = Board(Constants.WIDTH, Constants.HEIGHT, screen, difficulty)
    board.draw()
    
    while True:
        for event in pygame.event.get():
            # Quit program if the user closes the window
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()

            mouse_pos = pygame.mouse.get_pos()

            # Boolean's are checked when clicked and allows game to start based on gamemode selected
            if event.type == pygame.MOUSEBUTTONDOWN:
                if easy_button_rect.collidepoint(mouse_pos):
                    easy_button_clicked = True
                    medium_button_clicked = True
                    hard_button_clicked = True
                    board = Board(Constants.WIDTH, Constants.HEIGHT, screen, 30)
                if medium_button_rect.collidepoint(mouse_pos):
                    easy_button_clicked = True
                    medium_button_clicked = True
                    hard_button_clicked = True
                    board = Board(Constants.WIDTH, Constants.HEIGHT, screen, 40)
                if hard_button_rect.collidepoint(mouse_pos):
                    easy_button_clicked = True
                    medium_button_clicked = True
                    hard_button_clicked = True
                    board = Board(Constants.WIDTH, Constants.HEIGHT, screen, 50)
        
            # The if statements that check if the cursor is over a gamemode to highlight the text
            # based on that difficulty
            if not easy_button_clicked and easy_button_rect.collidepoint(mouse_pos):
                easy_button = draw_text("EASY", button_font, EASY_HIGHTLIGHT_COLOR, 100, 600)
            elif not easy_button_clicked:
                easy_button = draw_text("EASY", button_font, TEXT_COL, 100, 600)
        
            if not medium_button_clicked and medium_button_rect.collidepoint(mouse_pos):
                medium_button = draw_text("MEDIUM", button_font, MEDIUM_HIGHTLIGHT_COLOR, 325, 600)
            elif not medium_button_clicked:
                medium_button = draw_text("MEDIUM", button_font, TEXT_COL, 325, 600)
        
            if not hard_button_clicked and hard_button_rect.collidepoint(mouse_pos):
                hard_button = draw_text("HARD", button_font, HARD_HIGHTLIGHT_COLOR, 650, 600)
            elif not hard_button_clicked:
                hard_button = draw_text("HARD", button_font, TEXT_COL, 650, 600)
    
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
            # cell's value and skecthed value currently equal 0 (the cell is visually empty on the board)
                if event.key == pygame.K_1:
                    if cell.value == 0 and cell.sketched_value == 0:
                        board.sketch(1, row, col, cell)
                if event.key == pygame.K_2:
                    if cell.value == 0 and cell.sketched_value == 0:
                        board.sketch(2, row, col, cell)
                if event.key == pygame.K_3:
                    if cell.value == 0 and cell.sketched_value == 0:
                        board.sketch(3, row, col, cell)
                if event.key == pygame.K_4:
                    if cell.value == 0 and cell.sketched_value == 0:
                        board.sketch(4, row, col, cell)
                if event.key == pygame.K_5:
                    if cell.value == 0 and cell.sketched_value == 0:
                        board.sketch(5, row, col, cell)
                if event.key == pygame.K_6:
                    if cell.value == 0 and cell.sketched_value == 0:
                        board.sketch(6, row, col, cell)
                if event.key == pygame.K_7:
                    if cell.value == 0 and cell.sketched_value == 0:
                        board.sketch(7, row, col, cell)
                if event.key == pygame.K_8:
                    if cell.value == 0 and cell.sketched_value == 0:
                        board.sketch(8, row, col, cell)
                if event.key == pygame.K_9:
                    if cell.value == 0 and cell.sketched_value == 0:
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
                            # Redraw red rectangle around selected cell
                            cell = board.select(row, col)
    
                    if event.key == pygame.K_RETURN:
                        # Sets the sketched value of the selected cell to the cell value and re-draws the updated board
    
                        # Only does so if the value was not randomly generated (not entered by user)
                        if board.original_board[row][col] == 0:
                            cell.set_cell_value(cell.sketched_value)
                            board.update_board()
                            screen.fill(Constants.BG_COLOR)
                            board.draw()
                            # Redraw red rectangle around selected cell
                            cell = board.select(row, col)
                            
    
    
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

