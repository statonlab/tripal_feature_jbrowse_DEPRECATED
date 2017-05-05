<?php
/**
 * Create the form.
 *
 * @return mixed
 */
function tripal_feature_jbrowse_form($form, &$form_state, $id = NULL) {

  if ($id) {
    $record = db_query('SELECT * FROM tripal_feature_jbrowse WHERE id=:id', [
      ':id' => $id,
    ])->fetchObject();

    if ($record) {
      $organism_id = $record->organism_id;
      $title = $record->title;
      $link = $record->link;
      $tracks = implode(',', json_decode($record->tracks));
      $description = json_decode($record->description);
      $show = $record->show_in_organism_page;
    }
    else {
      return drupal_not_found();
    }
  }

  // Get the list of organisms
  $organisms = chado_query('select organism_id, common_name, genus, species from {organism}');

  $organisms_list = ['' => '-- Choose Organism --'];

  while ($organism = $organisms->fetchObject()) {
    $organisms_list[$organism->organism_id] = t("{$organism->common_name} ({$organism->genus} {$organism->species})");
  }

  $form['organism'] = [
    '#prefix' => '<p><b>Add a pane to the organism page that links to a JBrowse instance.</b></p>',
    '#title' => t('Organism'),
    '#type' => 'select',
    '#description' => t('Organism to associate a JBrowse instance to its features.'),
    '#options' => $organisms_list,
    '#attributes' => ['class' => ['form-control']],
    '#default_value' => isset($organism_id) ? $organism_id : current($organisms_list),
    '#required' => TRUE,
  ];

  $form['title'] = [
    '#type' => 'textfield',
    '#title' => t('Pane Title'),
    '#default_value' => isset($title) ? $title : t('JBrowse'),
    '#description' => t('The pane\'s link title.'),
    '#required' => TRUE,
  ];

  $form['link'] = [
    '#type' => 'textfield',
    '#title' => t('Feature JBrowse Link'),
    '#description' => t('Link to the JBrowse instance. Example: /jbrowse/?data=organism or https://example.com/jbrowse?data=organism.'),
    '#required' => TRUE,
    '#default_value' => isset($link) ? $link : '',
  ];

  $form['tracks'] = [
    '#type' => 'textfield',
    '#title' => t('JBrowse Tracks'),
    '#description' => t('Add a comma separated list of JBrowse tracks to display by default. Example: gene, MARKER1, Marker2.'),
    '#default_value' => isset($tracks) ? $tracks : '',
  ];

  $form['description'] = [
    '#type' => 'text_format',
    '#title' => t('Pane Page Content'),
    '#description' => t('Optional description for the pane. If left empty, clicking on the pane\'s link will redirect the user to JBrowse.'),
    '#default_value' => isset($description) ? $description->value : '',
    '#format' => isset($description) ? $description->format : '',
  ];

  $form['show_in_organism'] = [
    '#type' => 'checkbox',
    '#title' => t('Show link on organism page too.'),
    '#return_value' => 1,
    '#default_value' => isset($show) ? $show : 0,
  ];

  $form['id'] = [
    '#type' => 'hidden',
    '#value' => $id,
  ];

  $form['submit'] = [
    '#type' => 'submit',
    '#value' => 'Save',
  ];

  return $form;
}

/**
 * Handle form submission and add record to the database.
 *
 * @param $form
 * @param $form_sate
 *
 * @return void
 */
function tripal_feature_jbrowse_form_submit($form, &$form_sate) {
  $values = $form_sate['values'];
  $tracks = $values['tracks'] ? explode(',', $values['tracks']) : [];
  $id = $values['id'];

  $fields = [
    'organism_id' => $values['organism'],
    'title' => $values['title'],
    'link' => $values['link'],
    'tracks' => json_encode($tracks),
    'description' => json_encode($values['description']),
    'show_in_organism_page' => $values['show_in_organism'] ? 1 : 0,
  ];

  if ($id && $id > 0) {
    db_update('tripal_feature_jbrowse')
      ->fields($fields)
      ->condition('id', $id)
      ->execute();
  }
  else {
    // Insert records to the database
    db_insert('tripal_feature_jbrowse')->fields($fields)->execute();
  }

  drupal_set_message('Record saved successfully');
  drupal_goto('admin/tripal/extension/feature_jbrowse_link');
}

function tripal_feature_jbrowse_delete($id) {
  $delete = db_delete('tripal_feature_jbrowse')
    ->condition('id', $id, '=')
    ->execute();
  if ($delete) {
    drupal_set_message('Record deleted successfully.');
  }
  else {
    drupal_set_message('Could not delete the record. Please try again.', 'error');
  }

  drupal_goto('admin/tripal/extension/feature_jbrowse_link');

}