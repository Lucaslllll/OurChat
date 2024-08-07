# -*- coding: utf-8 -*-
import os

from kivymd.app import MDApp
from kaki.app import App
from kivy.factory import Factory

from kivy.clock import Clock
from kivy.storage.jsonstore import JsonStore

from kivy.core.window import Window
from kivy.config import Config
Window.softinput_mode = 'below_target'
Config.set('kivy', 'keyboard_mode', 'systemandmulti')
Config.set('kivy', 'exit_on_escape', 'False')


class OurChatApp(App, MDApp):
    def __init__(self, **kwargs):
        # herdará de buttonbehavior e label
        super(OurChatApp, self).__init__(**kwargs)



    # apenas na produção, lembrar de tira quando for compilar
    DEBUG = 1

    KV_FILES = {
        os.path.join(os.getcwd(), "screens/screenmanager.kv"),
        os.path.join(os.getcwd(), "screens/chat_screen/chat.kv"),
        os.path.join(os.getcwd(), "screens/default_screen/default.kv"),

    }


    CLASSES = {
        "MainScreenManager": "screens.screenmanager",
        "Chat": "screens.chat_screen.chat",
        "Default": "screens.default_screen.default",

    }


    AUTORELOADER_PATHS = [
        (".", {"recursive": True}),
    ]


    def build_app(self):
        self.theme_cls.theme_style = "Dark"
        return Factory.MainScreenManager()

OurChatApp().run()
