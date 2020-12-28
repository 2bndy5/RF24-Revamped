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
)
import recommonmark
from recommonmark.transform import AutoStructify
from recommonmark.parser import CommonMarkParser

sys.path.insert(0, os.path.abspath("."))

# -- Project information -----------------------------------------------------

project = "RF24 Revemped"
copyright = "2020, 2bndy5"
author = "2bndy5"

# The full version, including alpha/beta/rc tags
release = "2.0"


# -- General configuration ---------------------------------------------------

# Add any Sphinx extension module names here, as strings. They can be
# extensions coming with Sphinx (named 'sphinx.ext.*') or your custom
# ones.
extensions = [
    "breathe",
    "recommonmark",
    "sphinx.ext.autosectionlabel",
    # "sphinx.ext.intersphinx",
]

# intersphinx_mapping = {"python": ("https://docs.python.org/3.7", None)}

# Add any paths that contain templates here, relative to this directory.
templates_path = ["_templates"]

source_suffix = {
    ".rst": "restructuredtext",
    ".txt": "markdown",
    ".md": "markdown",
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
        # Name: "#9CDCFE",
        Name.Builtin: "#EAEB82",
        Name.Builtin.Pseudo: "#499DC7",
        Name.Class: "#48C999",
        Name.Decorator: "#EAEB82",
        Name.Exception: "#48C999",
        Name.Attribute: "#569CD6",
        Name.Variable:" #9CDCFE",
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

breathe_projects = {"RF24": "./doxygen/xml"}
breathe_default_project = "RF24"

# recommonmark Configuration
# -------------------------------------------------

def visit_document(*_):
    pass

# Removes irrelevant warning messages during md file parsing.
# REF: https://github.com/readthedocs/recommonmark/issues/177
# Hopefully will be unnecessary in the future (when recommonmark > 0.6.0 exists)
setattr(CommonMarkParser, "visit_document", visit_document)

# app setup hook
def setup(app):
    app.add_config_value(
        "recommonmark_config",
        {
            #'url_resolver': lambda url: github_doc_root + url,
            # 'auto_toc_tree_section': 'Contents',
            # 'enable_math': False,
            # 'enable_inline_math': False,
            "enable_eval_rst": True,
        },
        True,
    )
    app.add_transform(AutoStructify)


# Prefix document path to section labels, otherwise autogenerated labels would look like 'heading'
# rather than 'path/to/file:heading'
# autosectionlabel_prefix_document = True

# ReadTheDocs configuration
# ---------------------------------------------
read_the_docs_build = os.environ.get("READTHEDOCS", None) == "True"

if read_the_docs_build:
    subprocess.call("doxygen", shell=True)

# Options for HTML output
# -------------------------------------------------

# The theme to use for HTML and HTML Help pages.  See the documentation for
# a list of builtin themes.
#
html_theme = "sphinx_rtd_theme"

# Add any paths that contain custom static files (such as style sheets) here,
# relative to this directory. They are copied after the builtin static files,
# so a file named "default.css" will overwrite the builtin "default.css".
html_static_path = ["_static"]

# These paths are either relative to html_static_path
# or fully qualified paths (eg. https://...)
html_css_files = [
    "darkness.css",
]

# The name of an image file (relative to this directory) to use as a favicon of
# the docs.  This file should be a Windows icon file (.ico) being 16x16 or 32x32
# pixels large.
#
html_favicon = "_static/favicon.ico"

html_logo = "_static/Logo.png"

# Output file base name for HTML help builder.
htmlhelp_basename = "RF24RevampedLibrarydoc"