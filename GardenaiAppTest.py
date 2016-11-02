import kivy
kivy.require('1.0.6') # replace with your current kivy version !

from kivy.app import App
from kivy.uix.label import Label
from kivy.uix.gridlayout import GridLayout


class HomeScreen(GridLayout):

	def __init__(self, **kwargs):
		super(HomeScreen, self).__init__(**kwargs)
		self.cols = 2
		self.add_widget(Label(Text="Plant Name:"))
		self.add_widget(Label(Text="Tom Gore"))
		self.add_widget(Label(Text="Plant Type:"))
		self.add_widget(Label(Text="Thyme"))

class GardenaiApp(App):

    def build(self):
        return Label(text='Hello world')


if __name__ == '__main__':
    GardenaiApp().run()
	
