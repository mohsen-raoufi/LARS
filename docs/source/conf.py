# Configuration file for the Sphinx documentation builder.
#
# For the full list of built-in configuration values, see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

import os
import sys
sys.path.insert(0, os.path.abspath('.'))

extensions = [
    'breathe',
]

breathe_projects = {
    "LARS": "../doxygen/xml"   # <-- Edit this path to where doxygen's xml/ folder is
}
breathe_default_project = "LARS"

html_theme = "sphinx_rtd_theme"


# -- Project information -----------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#project-information

project = 'LARS'
copyright = '2025, Mohsen Raoufi'
author = 'Mohsen Raoufi'
release = '2.1'

# -- General configuration ---------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#general-configuration

templates_path = ['_templates']
exclude_patterns = []



# -- Options for HTML output -------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#options-for-html-output

html_theme = 'alabaster'
html_static_path = ['_static']
