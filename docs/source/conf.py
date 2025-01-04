# Configuration file for the Sphinx documentation builder.
#
# For the full list of built-in configuration values, see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Path setup --------------------------------------------------------------
from cgitb import html
import os
import sys
sys.path.insert(0, os.path.abspath('../../'))
sys.path.append("../breathe/")

# -- Project information -----------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#project-information

project = 'Power Monitor'
copyright = 'since 2020 - AgroTechLab'
author = 'Robson Costa'
version = '1.3'
release = '1.3.0'

# -- General configuration ---------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#general-configuration

need_sphinx = '8.1.3'
extensions = [
    'sphinx.ext.autodoc',
    'sphinx.ext.autosummary',
    'sphinx.ext.todo',
    'sphinx.ext.napoleon', 
    'sphinx.ext.ifconfig',
    'sphinx.ext.viewcode',
    'sphinx.ext.graphviz',
    'sphinx.ext.githubpages',
    'breathe',
]
today_fmt = '%d/%m/%Y'
numfig = True
primary_domain = 'cpp'
show_authors = True
master_doc = 'index'
templates_path = ['_templates']
exclude_patterns = []

# -- Breathe configuration ---------------------------------------------------
# https://breathe.readthedocs.io/en/latest/quickstart.html#configuration
breathe_projects = {
    "Power Monitor": "../doxygen/xml/"
}
breathe_default_project = "Power Monitor"

# -- Options for HTML output -------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#options-for-html-output

html_theme = 'sphinx_rtd_theme'
html_static_path = ['_static']
