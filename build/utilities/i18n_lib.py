#!/usr/bin/env python3
"""Module to interact with the i18n files easily."""
# Base imports
import contextlib
import copy
import logging
import os


class Key:
    """Class to represent a key in the i18n file."""

    def __init__(self, line: str, filename: str):
        """Initialize the key.

        Args:
            line (str): The line to parse.
            file (str): The original file name.
        """
        # Initialise the line
        self.line: str = line
        self.file: str = filename
        self.is_active: bool = True
        # Set the key and value as empty to avoid errors
        self.key = self.line
        self.value = ''
        # Parse the line
        self.parse_line()
        # Get the language from the file name
        self.language = self.file.split('.')[-2]

    def parse_line(self):
        """Parse the line."""
        # Remove spaces around the = and around the line but not in the value
        self.remove_spaces()
        # Handle the comment
        if self.line.startswith('#'):
            self.is_active = False
            return
        # Handle empty lines
        if self.line.strip() == '':
            self.is_active = False
            return
        # Handle lines with only a key
        if '=' not in self.line:
            self.is_active = False
            return
        # Split the line
        line_split = self.line.split('=')
        # Handle line with =
        self.key: str = line_split[0].strip()
        # Add to the value all the other parts of the line
        self.value: str = '='.join(line_split[1:]).strip()
        # Remove the quotes
        self.value = self.value[1:-1]

    def remove_spaces(self):
        """Remove spaces around the = and the line."""
        # Remove spaces around the =
        self.line = self.line.replace(' = ', '=')
        self.line = self.line.replace('= ', '=')
        # Remove spaces around the line
        # Remove space at the beginning of the line
        self.line = self.line.lstrip()
        # Remove space at the end of the line
        self.line = self.line.rstrip()

    def get_filename(self, locale=""):
        """Get the filename of the key.

        Args:
            locale (str): The locale to use.
        """
        # Get the filename
        filename = self.file
        # If the locale is empty, return the filename
        if locale == "":
            return filename
        # If the locale is not empty, update the filename with the locale
        filename = filename.replace(f".{self.language}", f".{locale}")
        return filename


class I18nData:
    """Class to interact with the i18n files easily."""

    def __init__(self, base_path=".", dry_run=False, ignore_universal=False,
                 base_locale="fr"):
        """Initialise the class.

        Args:
            base_path (str, optional): The base path to search i18n files.
                                       Defaults to ".".
            dry_run (bool, optional): Weather to skip the writing of the files.
                                      Defaults to False.
            ignore_universal (bool, optional): Weather to ignore the universal
                                               keys. Defaults to False.
            base_locale (str, optional): The base locale. Defaults to "en".
        """
        # Log the initialisation
        logging.info("Initialising i18n data")
        # Initialise the class
        self.data = {}
        self.encoding = "utf-8"
        # Log the settings
        logging.debug("Settings:")
        logging.debug("  Base path: %s", base_path)
        logging.debug("  Dry run: %s", dry_run)
        logging.debug("  Ignore universal: %s", ignore_universal)
        logging.debug("  Base locale: %s", base_locale)
        # Save the settings
        self.base_path = base_path
        self.dry_run = dry_run
        self.ignore_universal = ignore_universal
        self.base_locale = base_locale
        # Load the i18n files
        self.load_i18n()
        # Sort the i18n data
        self.sort_i18n_data(self.base_locale)

    def load_i18n(self):
        """Load the i18n files."""
        # Log the loading
        logging.debug("Loading i18n files")
        # Clear the current data
        self.data = {}
        # Get the i18n files
        i18n_files = self.get_i18n_files()
        # Sort the i18n files
        self.data = self.sort_i18n_files(i18n_files)
        # Remove the universal keys if needed
        if self.ignore_universal:
            self.remove_locale("universal")

    def remove_locale(self, locale: str):
        """Remove the locale.

        Args:
            locale (str): The locale to remove.
        """
        # Log the removal
        logging.info("Removing locale %s", locale)
        # Remove the locale
        self.data.pop(locale, None)

    def get_i18n_files(self) -> list[str]:
        """Get the i18n files.

        Returns:
            list: The i18n files.
        """
        # Log the loading
        logging.debug("Getting i18n files")
        # Get the i18n files
        i18n_files: list[str] = []
        # Get the i18n files
        for root, _, files in os.walk(self.base_path):
            # Get the i18n files in the current directory by filtering the
            # extension
            i18n_files.extend(
                os.path.join(root, file)
                for file in files if file.endswith(".i18n")
            )
        # Return the i18n files
        return i18n_files

    def sort_i18n_files(self, i18n_files: list) -> dict[str, list[Key]]:
        """Sort the i18n files.

        Args:
            i18n_files (list): The i18n files.

        Returns:
            dict: The i18n files sorted by language.
        """
        # Log the loading
        logging.debug("Sorting i18n files")
        # Sort the i18n files
        i18n_files_language: dict[str, list[Key]] = {}
        # Sort the i18n files
        for i18n_file in i18n_files:
            # Get the language
            language = i18n_file.split(".")[-2]
            # Add the language to the list
            if language not in i18n_files_language:
                i18n_files_language[language] = []
            # Get the i18n data
            i18n_data = self.get_i18n_data(i18n_file)
            # Add the i18n data
            i18n_files_language[language].extend(i18n_data)
        # Return the i18n files
        return i18n_files_language

    def get_i18n_data(self, i18n_file: str) -> list[Key]:
        """Get the i18n data.

        Args:
            i18n_file (str): The i18n file.

        Returns:
            dict: The i18n data.
        """
        # Log the loading
        logging.debug("Getting i18n data from %s", i18n_file)
        # Get the i18n data
        i18n_data: list[Key] = []
        # Get the i18n data
        with open(i18n_file, "r", encoding=self.encoding) as i18n_file_handle:
            # Parse the lines
            for line in i18n_file_handle.read().splitlines():
                # Get the key
                key = Key(line, i18n_file)
                # Add the key
                i18n_data.append(key)
        # Return the i18n data
        return i18n_data

    def sort_i18n_data(self, original_order="") -> None:
        """Sort the i18n data.

        Args:
            original_order (str): The original locale for the order of the
                                  i18n data.

        Sorting is done by copying the order of the original locale.
        """
        # Log the sorting
        logging.debug("Sorting i18n data")
        # If the original order is empty, use the base locale
        if original_order == "":
            original_order = self.base_locale
        # Extract the original order
        original_order_data = self.data[original_order]
        # Extract the keys names from the original order
        original_order_keys = [key.key for key in original_order_data]
        # Sort the keys
        for language, data in self.data.items():
            # Ignore the original order and the universal order
            if language in [original_order, "universal"]:
                continue
            # Sort the data
            try:
                data.sort(key=lambda key: original_order_keys.index(key.key))
            except ValueError:
                logging.warning("Could not sort the i18n data for %s",
                                language)
            # Update the data
            self.data[language] = data

    def write_data(self) -> None:
        """Save the i18n data to the disk."""
        # Log the writing
        logging.info("Writing i18n data")
        # Get if dry run is enabled
        if self.dry_run:
            # Log the dry run
            logging.info("Dry run enabled, files will be only generated")
        # Sort the i18n data
        self.sort_i18n_data(self.base_locale)
        # Iterate over the languages
        for language, data in self.data.items():
            # Generate locale's files
            files: dict[str, str] = self.generate_locale_files(language, data)
            # Write the files
            self.write_locale_files(files)

    def generate_locale_files(self, language: str, data: list[Key]) ->\
            dict[str, str]:
        """Generate the locale's files.

        Args:
            language (str): The language.
            data (list): The i18n data.

        Returns:
            list: The locale's files.
        """
        # Log the generation
        logging.debug("Generating locale's files for %s", language)
        # Generate the locale's files
        keys: dict[str, list[Key]] = {}
        # Get the keys by file, to handle bad sorting
        for key in data:
            # Get the file
            file = key.file
            # Add the file to the list
            if file not in keys:
                keys[file] = []
            # Add the key
            keys[file].append(key)
        # Return the files
        return {
            file:
            self.generate_file(language, file, keys)
                for file, keys in keys.items()
        }

    def generate_file(self, language: str, file: str, data: list[Key]) -> str:
        """Generate the locale's file.

        Args:
            language (str): The language.
            file (str): The file.
            data (list): The i18n data.

        Returns:
            str: The locale's file.
        """
        # Log the generation
        logging.debug("Generating locale's file for %s in %s", language, file)
        # Generate the locale's file
        file_data = ""
        # Iterate over the keys
        for key in data:
            # Check if the line is active
            if not key.is_active:
                file_data += f"{key.line}\n"
                continue
            # Else, generate the line
            file_data += f"{key.key} = \"{key.value}\"\n"
        # Return the file
        return file_data

    def write_locale_files(self, files: dict[str, str]) -> None:
        """Write the locale's files.

        Args:
            files (dict): The locale's files.
        """
        # Log the writing
        logging.debug("Writing locale's files")
        # Iterate over the files
        for file, content in files.items():
            # Write the file
            self.write_file(file, content)

    def write_file(self, file: str, content: str) -> None:
        """Write the file.

        Args:
            file (str): The file.
            content (str): The content.
        """
        # Log the writing
        logging.debug("Writing file %s", file)
        # Get the actual file
        with open(file, "r", encoding=self.encoding) as file_handle:
            # Get the file content
            file_content = file_handle.read()
        # Check if the file content is different
        if file_content == content:
            # Log the file is up to date
            logging.debug("File %s is up to date", file)
            # Return
            return
        # Write the file if not in dry run
        if not self.dry_run:
            with open(file, "w", encoding=self.encoding) as file_handle:
                file_handle.write(content)

    def get_languages(self) -> list[str]:
        """Get the languages.

        Returns:
            list: The languages.
        """
        # Log the loading
        logging.info("Getting languages")
        # Get the languages
        return [language for language, data in self.data.items()]

    def get_keys(self, locale="all") -> list[Key]:
        """Get the keys.

        Args:
            locale (str): The locale. Defaults to all.

        Returns:
            list: The keys.
        """
        # Log the loading
        logging.debug("Getting all keys")
        # Get the keys
        keys = []
        # Iterate over the languages if all
        if locale == "all":
            for _, data in self.data.items():
                # Add the keys
                keys.extend(data)
        # Else, get the keys for the locale
        else:
            # Get the keys
            keys = self.data[locale]
        # Return the keys
        return keys

    def get_keys_names(self, locale="all") -> list[str]:
        """Get the keys names.

        Args:
            locale (str): The locale. Defaults to all.

        Returns:
            list: The keys names.
        """
        # Log the loading
        logging.debug("Getting keys names")
        # Get the keys names
        keys_names = [key.key for key in self.get_keys(locale=locale)]
        # Remove the duplicates
        return list(set(keys_names))

    def get_key(self, key_name: str, locale: str) -> Key:
        """Get the key.

        Args:
            key (str): The key.
            locale (str): The locale.

        Returns:
            Key: The key.
        """
        # Log the loading
        logging.debug("Getting key %s in %s", key_name, locale)
        # If locale is all, return the first match
        if locale == "all":
            # Iterate over the languages
            for language, _ in self.data.items():
                # Try to get the key
                try:
                    # Return the key if found
                    return self.get_key(key_name, language)
                except KeyError:
                    continue
            # If no key was found, raise an error
            raise KeyError(f"Key {key_name} not found in any language")
        # Print all the keys in the locale
        for key_iter in self.get_keys(locale=locale):
            # Check if the key is the same
            if key_iter.key == key_name:
                # Return the key
                return key_iter
        # Raise an error if the key is not found
        raise KeyError(f"Key {key_name} not found in {locale}")

    def get_key_index(self, key: str, locale="all") -> int:
        """Get the key index.

        Args:
            key (str): The key.
            locale (str): The locale. Defaults to all.

        Returns:
            int: The key index.
        """
        # Log the loading
        logging.debug("Getting key index for %s in %s", key, locale)
        # Get the key index
        key_index = -1
        # Iterate over the languages if all
        if locale == "all":
            for _, data in self.data.items():
                # Try to get the key index
                with contextlib.suppress(KeyError):
                    # Get the key index
                    key_index = data.index(self.get_key(key, locale=_))
                    # Break the loop
                    break
        else:
            # Get the key index
            key_index = self.data[locale].index(self.get_key(key, locale))
        # Raise an error if the key is not found
        if key_index == -1:
            raise KeyError(f"Key {key} not found in {locale}")
        # Return the key index
        return key_index

    def get_value(self, key: str, locale: str) -> str:
        """Get the value.

        Args:
            key (str): The key.
            locale (str): The locale.

        Returns:
            str: The value.
        """
        # Log the loading
        logging.info("Getting value for %s in %s", key, locale)
        # Get the value
        return self.get_key(key, locale).value

    def set_value(self, key: str, locale: str, value: str) -> None:
        """Set the value.

        Args:
            key (str): The key.
            locale (str): The locale.
            value (str): The value.
        """
        # Log the setting
        logging.info("Setting value for %s in %s to %s", key, locale, value)
        # Set the value
        self.get_key(key, locale).value = value

    def remove_key(self, key: str, locale_origin="all") -> None:
        """Remove the key.

        Args:
            key (str): The key.
            locale (str): The locale. Defaults to all.
        """
        # Log the removing
        logging.info("Removing key %s in %s", key, locale_origin)
        # If the locale is all, remove the key from all locales
        if locale_origin == "all":
            # Iterate over the locales
            for locale in self.data:
                # Remove the key
                self.remove_key(key, locale)
            # Return
            return
        # Else, remove the key from the locale
        self.data[locale_origin].pop(self.get_key_index(key, locale_origin))

    def key_exists(self, key: str, locale: str) -> bool:
        """Check if the key exists.

        Args:
            key (str): The key.
            locale (str): The locale.

        Returns:
            bool: True if the key exists, False otherwise.
        """
        # Log the checking
        logging.debug("Checking if key %s in %s exists", key, locale)
        # Check if the key exists
        try:
            # Get the key
            self.get_key(key, locale)
            # Return true
            return True
        # Else, return false
        except KeyError:
            return False

    def get_missing_keys(self) -> dict[str, list[str]]:
        """Get the missing keys by comparing with other locales.

        Returns:
            dict: The missing keys as a dict with the locale as key and the
                  missing keys in a list as value.
        """
        # Log the loading
        logging.info("Getting missing keys")
        # Backup the data
        data_backup = self.data
        # Remove the universal locale
        self.remove_locale("universal")
        # Initialize the missing keys
        missing_keys: dict[str, list[str]] = {}
        # Get the keys names list
        keys_names = self.get_keys_names()
        # Iterate over the locales
        for locale in self.data:
            # Get the keys names
            keys_names_locale = self.get_keys_names(locale)
            # Get the missing keys
            missing_keys[locale] = [
                key for key in keys_names if key not in keys_names_locale
            ]
        # Restore the data
        self.data = data_backup
        # Return the missing keys
        return missing_keys

    def add_key(self, key: str, value: str, locale: str, filename=None) \
            -> None:
        """Add the key.

        Args:
            key (str): The key.
            locale (str): The locale.
            value (str): The value.
        """
        # Log the adding
        logging.info("Adding key %s in %s with value %s", key, locale, value)
        # Get if filename is given
        if filename:
            # Create the key
            key_obj = Key("", "")
            # Set the key
            key_obj.key = key
            # Set the value
            key_obj.value = value
            # Set the filename
            key_obj.key = filename
            # Set the locale
            key_obj.language = locale
        else:
            # Get the key index
            key_index = self.get_key_index(key, "all")
            # If the key doesn't exist, crash, because we can't guess the
            # filename
            if key_index == -1:
                raise ValueError("Key doesn't exist and no file were given")
            # Get the key
            key_obj_original = self.get_key(key, "all")
            # Copy the key; we don't want to modify the original key
            key_obj = copy.copy(key_obj_original)
            # Set the value
            key_obj.value = value
            # Update the filename to match the locale
            key_obj.file = key_obj.get_filename(locale)
        # Set the key as active
        key_obj.is_active = True
        # Add the key
        self.data[locale].append(key_obj)


class Tests:
    """Tests."""

    def test_rw(self):
        """Test the reading and writing."""
        # Load the i18n files
        i18n = I18nData()
        # Read the i18n raw data
        for language, keys in i18n.data.items():
            # Do nothing because we just want to test the format of the data
            pass
        # Sort the i18n data
        i18n.sort_i18n_data()
        # Read a part of the i18n data (the 10th key of each language),
        # each key name should be the same
        last_key: str = ""
        first_key: bool = True
        for language, keys in i18n.data.items():
            # Ignore universal
            if language == "universal":
                continue
            if not first_key:
                assert last_key == keys[10].key
            last_key = keys[10].key
            first_key = False
        # Write the i18n data
        i18n.write_data()

    def test_rw_dry_run(self):
        """Test the reading and writing in dry run."""
        # Load the i18n files
        i18n = I18nData(dry_run=True)
        # Remove some keys
        i18n.remove_key("SettingsApp", "fr")
        # Assert that the key is not in the data
        assert not i18n.key_exists("SettingsApp", "fr")
        # Write the i18n data
        i18n.write_data()
        # Reload the i18n data
        i18n = I18nData()
        # Check that the key is in the i18n data
        assert i18n.key_exists("SettingsApp", "fr")

    def test_languages(self):
        """Test the languages."""
        # Load the i18n files
        i18n = I18nData()
        # Get the languages
        languages = i18n.get_languages()
        # Log the languages
        logging.info("Languages: %s", languages)
        # Check that the languages are correct
        assert "universal" in languages
        assert "fr" in languages
        # Remove the universal language
        languages.remove("universal")
        # Check that the languages are correct
        assert "universal" not in languages
        assert "fr" in languages

    def test_keys_edit(self):
        """Test the keys edition."""
        # Load the i18n files
        i18n = I18nData(dry_run=True, ignore_universal=True)
        # Get the keys
        keys = i18n.get_keys()
        # Read the keys
        for key in keys:
            # Get the value
            value = key.value
            # Get the key name
            key_name = key.key
            # Get the locale
        # Get the keys names
        keys_names = i18n.get_keys_names()
        # Read keys names
        for key_name in keys_names[:5]:
            # Get the key
            key = i18n.get_key(key_name, "fr")
            # Get the value
            value = key.value
            # Get the key name
            key_name = key.key
            # Get the locale
            locale = key.language
            # Make the linter quiet about the unused variables
            assert value
            assert key_name
            assert locale
        # Assert that there is no duplicate key names
        assert len(keys_names) == len(set(keys_names))
        # Get a key
        key = i18n.get_key("SettingsApp", "fr")
        # Read the key
        key_name = key.key
        value = key.value
        # Get a value
        value = i18n.get_value("SettingsApp", "fr")
        # Set a value
        i18n.set_value("SettingsApp", "fr", "Test")
        # Get the value
        value = i18n.get_value("SettingsApp", "fr")
        # Assert that the value is correct
        assert value == "Test"
        # # Write the i18n data
        i18n.write_data()

    def test_keys_add_remove(self):
        """Test the keys addition and deletion."""
        # Load the i18n files
        i18n = I18nData(dry_run=True)
        # Remove a key
        i18n.remove_key("SettingsApp", "fr")
        # Assert that the key does not exist
        assert not i18n.key_exists("SettingsApp", "fr")
        # Add a key
        i18n.add_key("SettingsApp", "Test", "fr")
        # Assert that the key is in the i18n data
        assert i18n.key_exists("SettingsApp", "fr")
        # Write the i18n data
        i18n.write_data()

    def test_missing_keys(self):
        """Test the missing keys."""
        # Load the i18n files
        i18n = I18nData()
        # Get the missing keys
        missing_keys = i18n.get_missing_keys()
        # Log the missing keys
        logging.info("Missing keys: %s", missing_keys)


def main():
    """Run the tests."""
    # Initialise the logger
    logging.basicConfig(
        level=logging.INFO,
        format='%(asctime)s - %(levelname)s - %(message)s'
    )
    # Run the tests
    test_instance = Tests()
    test_instance.test_rw()
    test_instance.test_rw_dry_run()
    test_instance.test_languages()
    test_instance.test_keys_edit()
    test_instance.test_keys_add_remove()
    test_instance.test_missing_keys()


if __name__ == "__main__":
    main()
