import pygame.mouse
import pygame
pygame.init()

class Button:
    def __init__(self,text, x_pos, y_pos, enabled,where):
        self.text=text
        self.x_pos=x_pos
        self.y_pos=y_pos
        self.enabled=enabled
        self.where=where
        self.draw()

    def draw(self):
        font = pygame.font.SysFont("Grobold", 40)
        button_text=font.render(self.text, True, 'black')
        button_rect= pygame.rect.Rect((self.x_pos, self.y_pos), (120,50))
        if self.check_click():
            pass

        else:
            pygame.draw.rect(self.where, "grey",button_rect,0,5)
        pygame.draw.rect(self.where,"black", button_rect,2,5)
        self.where.blit(button_text,(self.x_pos+3, self.y_pos+3))

    def check_click(self):
        mouse_pos= pygame.mouse.get_pos()
        left_click=pygame.mouse.get_pressed()[0]
        button_rect=pygame.rect.Rect((self.x_pos, self.y_pos), (120,50))
        if left_click and button_rect.collidepoint(mouse_pos)and self.enabled:
            return True
        else:
            return False



