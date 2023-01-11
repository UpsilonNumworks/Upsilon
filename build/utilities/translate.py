#!/usr/bin/env python3
"""Generate missing translations for i18n files."""
import sys
import logging

import i18n_lib
try:
    from deep_translator import GoogleTranslator
except ModuleNotFoundError:
    print('Module deep_translator not found. Please install it with',
          '"pip3 install deep_translator"')
    sys.exit(1)


def translate(text: str, output_language: str, input_language: str = 'auto')\
        -> str:
    """Translate the given text.

    Args:
        text (str): The text to translate
        output_language (str): The output language
        input_language (str): The input language

    Returns:
        str: The translated text

    """
    # Ensure of the text exists (not empty)
    if not text:
        return ""
    # Initialize the translator
    translator = GoogleTranslator(source=input_language,
                                  target=output_language)
    # Translate and return the translated text
    return translator.translate(text)


def generate_missing_translations(i18n_data: i18n_lib.I18nData,
                                  missing_translations: dict[str, list[str]])\
        -> None:
    """Generate missing translations.

    Args:
        i18n_data (i18n_lib.I18nData): The i18n data.
        missing_translations (dict[str, list[str]]): The missing translations
                                                     by locale.
    """
    # Loop through the locales.
    for locale, missing_translations_locale in missing_translations.items():
        # Loop through the missing translations.
        for missing_translation in missing_translations_locale:
            # Get the key.
            value = i18n_data.get_value(missing_translation, "all")
            # Get the translation.
            translation = translate(value, locale)
            # Log the translation.
            logging.info("%s: %s -> %s", locale, missing_translation,
                         translation)
            # Add the key to the locale.
            i18n_data.add_key(missing_translation, translation, locale)


def main():
    """Run the script."""
    # Initialise the logger
    logging.basicConfig(
        level=logging.INFO,
        format='%(asctime)s - %(levelname)s - %(message)s'
    )
    # Load the i18n files.
    i18n_data = i18n_lib.I18nData()
    # Get the missing translations.
    missing_translations = i18n_data.get_missing_keys()
    # Generate the missing translations.
    generate_missing_translations(i18n_data, missing_translations)
    # Save the i18n files.
    i18n_data.write_data()


if __name__ == '__main__':
    main()
