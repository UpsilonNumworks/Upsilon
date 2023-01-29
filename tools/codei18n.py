## Helper to auto-generate translations

from googletrans import Translator
import os, regex

translator = Translator()

toTranslate = input("Text to translate (ex: sets the color of the led) -> ")
func_name = input("Func name (ex: modion_set_led_color)-> ")

def cap(l:list[str]) -> str:
    return "".join([word.capitalize() for word in l])

for file in os.listdir("./apps/code/"):
    if regex.match(r"catalog\.\w{2}\.i18n", file):
        targetLang = file.split(".")[1]
        translated = translator.translate(toTranslate, dest=targetLang, src="en").text
        pythonFunc = "Python" + (cap(func_name[6:].split("_")))
        with open("./apps/code/" + file, "a") as f:
            f.write("\n" + pythonFunc + " = " + '"' +translated + '"')

with open("./apps/code/catalog.universal.i18n", "a") as f:
    pythonCommand = "PythonCommand" + (cap(func_name[6:].split("_")))
    f.write("\n" + pythonCommand + " = " + '"' + func_name[6:] + '()"')