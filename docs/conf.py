# Configuration file for the Sphinx documentation builder.
#
# This file only contains a selection of the most common options. For a full
# list see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Path setup --------------------------------------------------------------

# If extensions (or modules to document with autodoc) are in another directory,
# add these directories to sys.path here. If the directory is relative to the
# documentation root, use os.path.abspath to make it absolute, like shown here.
#
import os
import sys
import subprocess
import pygments.styles
from pygments.style import Style
from pygments.token import (
    Text,
    Other,
    Comment,
    Keyword,
    Name,
    Literal,
    String,
    Number,
    Operator,
    Punctuation,
)

sys.path.insert(0, os.path.abspath("."))

# Project information -----------------------------------------------------

project = "RF24Revemped"
copyright = "2020, 2bndy5"
author = "2bndy5"

# The full version, including alpha/beta/rc tags
release = "2.0"

# sitemap configuration
# -------------------------------------------------

# set the base url, language, and version for sitemap generation
html_baseurl = "https://rf24-revamped.readthedocs.io/"
language = "en"
version = "latest"

# General configuration ---------------------------------------------------

# Add any Sphinx extension module names here, as strings. They can be
# extensions coming with Sphinx (named 'sphinx.ext.*') or your custom
# ones.
extensions = [
    "breathe",
    "sphinx_copybutton",
    "sphinx_sitemap",
    # "sphinx.ext.intersphinx",
]

# intersphinx_mapping = {"python": ("https://docs.python.org/3.7", None)}

# Add any paths that contain templates here, relative to this directory.
templates_path = ["_templates"]

source_suffix = {
    ".rst": "restructuredtext",
}

# The master toctree document.
master_doc = "index"

# List of patterns, relative to source directory, that match files and
# directories to ignore when looking for source files.
# This pattern also affects html_static_path and html_extra_path.
exclude_patterns = [
    "_build",
    "Thumbs.db",
    ".DS_Store",
    ".env",
    "CODE_OF_CONDUCT.md",
    "requirements.txt",
]

# The reST default role (used for this markup: `text`) to use for all
# documents.
# default_role = "any"

# add_function_parentheses = False

# Tell sphinx what the primary language being documented is.
primary_domain = "cpp"

# pygment custom style
# --------------------------------------------------


class DarkPlus(Style):
    """A custom pygment highlighting scheme based on
    VSCode's builtin `Dark Plus` theme"""

    background_color = "#1E1E1E"
    highlight_color = "#ff0000"
    line_number_color = "#FCFCFC"
    line_number_background_color = "#282828"

    default_style = ""
    styles = {
        Text: "#FEFEFE",
        Comment.Single: "#5E9955",
        Comment.Multiline: "#5E9955",
        Comment.Preproc: "#B369BF",
        Other: "#FEFEFE",
        Keyword: "#499CD6",
        Keyword.Declaration: "#C586C0",
        Keyword.Namespace: "#B369BF",
        # Keyword.Pseudo: "#499CD6",
        # Keyword.Reserved: "#499CD6",
        Keyword.Type: "#48C999",
        Name: "#FEFEFE",
        Name.Builtin: "#EAEB82",
        Name.Builtin.Pseudo: "#499DC7",
        Name.Class: "#48C999",
        Name.Decorator: "#EAEB82",
        Name.Exception: "#48C999",
        Name.Attribute: "#569CD6",
        Name.Variable: " #9CDCFE",
        Name.Variable.Magic: "#EAEB82",
        Name.Function: "#EAEB82",
        Name.Function.Magic: "#EAEB82",
        Literal: "#AC4C1E",
        String: "#B88451",
        String.Escape: "#DEA868",
        String.Affix: "#499DC7",
        Number: "#B3D495",
        Operator: "#FEFEFE",
        Operator.Word: "#499DC7",
        Punctuation: "#FEFEFE",
    }


def pygments_monkeypatch_style(mod_name, cls):
    """ function to inject a custom pygment style """
    cls_name = cls.__name__
    mod = type(__import__("os"))(mod_name)
    setattr(mod, cls_name, cls)
    setattr(pygments.styles, mod_name, mod)
    sys.modules["pygments.styles." + mod_name] = mod
    pygments.styles.STYLE_MAP[mod_name] = mod_name + "::" + cls_name


pygments_monkeypatch_style("dark_plus", DarkPlus)

# The name of the Pygments (syntax highlighting) style to use.
pygments_style = "dark_plus"

# Tell sphinx what the pygments highlight language should be.
highlight_language = "cpp"


# breathe configuration
# ---------------------------------------------

# autodoxygen directives are not as useful as you think
# breathe_projects_source = {
#     "RF24":
#     ("../", ["RF24.h", "RF24.cpp", "RF24_config.h", "nRF24L01.h"])
# }

breathe_projects = {"RF24Revamped": "./doxygen/xml"}
breathe_default_project = "RF24Revamped"

# ReadTheDocs configuration
# ---------------------------------------------
read_the_docs_build = os.environ.get("READTHEDOCS", None) == "True"

if read_the_docs_build:
    subprocess.call("doxygen", shell=True)

# Options for HTML output
# -------------------------------------------------

# The theme to use for HTML and HTML Help pages.  See the documentation for
# a list of builtin themes.
html_theme = "sphinx_material"

# Material theme options
html_sidebars = {
    "**": ["logo-text.html", "globaltoc.html", "localtoc.html", "searchbox.html"]
}
html_theme_options = {
    # Set the name of the project to appear in the navigation.
    "nav_title": "RF24 Revamped",
    # Set the color and the accent color
    "color_primary": "blue",
    "color_accent": "light-blue",
    # Set the repo location to get a badge with stats
    "repo_url": "https://github.com/2bndy5/RF24Revamped/",
    "repo_name": "RF24Revamped",
    # Visible levels of the global TOC; -1 means unlimited
    "globaltoc_depth": 1,
    # If False, expand all TOC entries
    "globaltoc_collapse": True,
    # If True, show hidden TOC entries
    "globaltoc_includehidden": True,
}

# Add any paths that contain custom static files (such as style sheets) here,
# relative to this directory. They are copied after the builtin static files,
# so a file named "default.css" will overwrite the builtin "default.css".
html_static_path = ["_static"]

# These paths are either relative to html_static_path
# or fully qualified paths (eg. https://...)
html_css_files = [
    "dark_material.css",
]

# Set link name generated in the top bar.
html_title = "RF24 Revamped"

# The name of an image file (relative to this directory) to use as a favicon of
# the docs.  This file should be a Windows icon file (.ico) being 16x16 or 32x32
# pixels large.
html_favicon = "_static/favicon.ico"

html_logo = "_static/Logo large.png"

# Output file base name for HTML help builder.
htmlhelp_basename = "RF24RevampedLibrarydoc"
