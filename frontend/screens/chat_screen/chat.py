from kivy.core.window import Window
from kivy.clock import Clock
from kivy.uix.label import Label

from kivymd.uix.snackbar import Snackbar
# from kivymd.uix.snackbar.snackbar import MDSnackbarActionButton
from kivymd.uix.label import MDLabel
from kivymd.uix.boxlayout import MDBoxLayout
from kivy.metrics import dp
from kivymd.uix.screen import MDScreen

from kaki.app import App
# from kivy.base import EventLoop
from kivy.core.window import Window




class Chat(MDScreen):
    
    def callback(self):
    	print("Olá")



class MessageLayout(MDBoxLayout):
    def __init__(self, texto, **kwargs):
        super().__init__(**kwargs)
        self.text = texto
        self.add_widget(Message(text=self.text))
        


class Message(Label):
    def __init__(self, **kwargs):
        super().__init__(**kwargs)
        self.size_hint = (1, None)
        self.font_size = sp(12)

    def on_size(self, *args):
        self.text_size = (self.width - sp(10), None)

    def on_texture_size(self, *args):
        self.size = self.texture_size
        self.height += sp(20)


class MessageOtherLayout(MDBoxLayout):
    def __init__(self, texto, **kwargs):
        super().__init__(**kwargs)
        self.text = texto
        self.add_widget(MessageOther(text=self.text))
        


class MessageOther(Label):
    def __init__(self, **kwargs):
        super().__init__(**kwargs)
        self.size_hint = (1, None)
        self.font_size = sp(12)

    def on_size(self, *args):
        self.text_size = (self.width - sp(10), None)

    def on_texture_size(self, *args):
        self.size = self.texture_size
        self.height += sp(20)