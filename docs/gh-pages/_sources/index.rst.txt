.. Power Monitor documentation master file, created by
   sphinx-quickstart on Fri Jan  3 10:09:21 2025.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

Power Monitor 
=============

**Power Monitor** is a IoT tool developed by `AgroTechLab <https://agrotechlab.lages.ifsc.edu.br>`_ (*Technology Development 
Laboratory for Agribusiness*) of `IFSC <https://www.ifsc.edu.br>`_ (*Federal Institute of Santa Catarina*).

It aims to get data about the energy consumption of IoT devices. Actual, average, minimum and maximum values are sampled
at each 50 ms. This values are updated at each 3 seconds on LCD interface. It provides the following information:

   - Actual voltage (in V);
   - Average voltage (in V);
   - Minimal voltage (in V);
   - Maximum voltage (in V);
   - Actual current (in mA);
   - Average current (in mA);
   - Minimal current (in mA);
   - Maximum current (in mA);

.. image:: _static/powermonitor_display.jpg
   :align: center
   :alt: Power Monitor Display


Versions support
----------------

Updates and new features are constantly being added to **Power Monitor**. The following table shows the supported versions:

.. table::
   :align: center
   :widths: 20 20 20   

   +---------+------------+--------------+
   | Version |  Security  | New features |
   +=========+============+==============+
   |  1.x.x  |     Yes    |     Yes      |
   +---------+------------+--------------+

.. toctree::
   :name: mastertoc
   :maxdepth: 2
   :caption: Table of Contents:

   authors_license
   changelog
   hw_req
   source_code_docs