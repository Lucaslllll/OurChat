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
from kivy.clock import Clock
from kivymd.uix.card import MDCardSwipe
from kivy.properties import StringProperty


class Default(MDScreen):
    
    def on_pre_enter(self):
        Clock.schedule_once(self.on_start, 1)

    def on_start(self, *args, **kwargs):

        for i in range(20):
            self.ids.list_contacts.add_widget(
                SwipeToDeleteItem(text=f"One-line item {i}")
            )


class SwipeToDeleteItem(MDCardSwipe):
    text = StringProperty()