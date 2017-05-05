## Introduction
This is a [Tripal](https://github.com/tripal/tripal) extension that provides a method for administrators to add a JBrowse link to certain feature pages based on the parent organism. It allows for the pane link to either directly transfer the user to the JBrowse instance or show a tab page that contains some description and a direct link to the JBrowse instance.

## Installation
Simply download or clone the modules into your `[Drupal installation path]/sites/all/modules/` and enable it using `drush` or the admin panel.

## Usage
A link menu will appear in the admin page titled *Tripal Feature Jbrowse* that links to `admin/tripal/extension/feature_jbrowse_link`. This will redirect the user to a list of existing links. 
To add a new item, click on the "Add" link. Once the form is submitted, all features that belong to the chosen organism will have a new pane link that can be found on the left sidebar. The link will display the title entered in the form.
To edit an item, visit the module's page `admin/tripal/extension/feature_jbrowse_link` and click the edit link for the item you'd like to edit. Deleting an item is also done in the same page.

## Issues & Contributions
Please report any issues in the GitHub [issue tracker](https://github.com/statonlab/tripal_feature_jbrowse/issues).

Contributions are always welcome and appreciated!

## License
This tool is licensed under the Apache 2.0 license. The details of which can be found on the [Apache website](http://www.apache.org/licenses/LICENSE-2.0).

The license notice can be found in the [License](https://github.com/statonlab/tripal_feature_jbrowse/blob/master/License) file.
