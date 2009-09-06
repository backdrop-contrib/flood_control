<?php
// $Id$

/**
 * @file
 * Administrative page callbacks for the flood_control module.
 */

/**
 * Administration settings form.
 *
 * @see system_settings_form()
 */
function flood_control_settings_form() {
  // User module flood events.
  $form['login'] = array(
    '#type' => 'fieldset',
    '#title' => t('Login'),
  );
  $form['login']['user_failed_login_ip_limit'] = array(
    '#type' => 'select',
    '#title' => t('Failed login (IP) limit'),
    '#options' => drupal_map_assoc(array(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 20, 30, 40, 50)),
    '#default_value' => 50,
  );
  $form['login']['user_failed_login_ip_window'] = array(
    '#type' => 'select',
    '#title' => t('Failed login (IP) window'),
    '#options' => array(0 => t('None (disabled)')) + drupal_map_assoc(array(60, 180, 300, 600, 900, 1800, 2700, 3600, 10800, 21600, 32400, 43200, 86400), 'format_interval'),
    '#default_value' => 3600,
  );
  $form['login']['user_failed_login_user_limit'] = array(
    '#type' => 'select',
    '#title' => t('Faild login (username) limit'),
    '#options' => drupal_map_assoc(array(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 20, 30, 40, 50)),
    '#default_value' => 5,
  );
  $form['login']['user_failed_login_user_window'] = array(
    '#type' => 'select',
    '#title' => t('Failed login (username) window'),
    '#options' => array(0 => t('None (disabled)')) + drupal_map_assoc(array(60, 180, 300, 600, 900, 1800, 2700, 3600, 10800, 21600, 32400, 43200, 86400), 'format_interval'),
    '#default_value' => 21600,
  );

  // Contact module flood events.
  $form['contact'] = array(
    '#type' => 'fieldset',
    '#title' => t('Contact forms'),
  );
  $form['contact']['contact_hourly_threshold'] = array(
    '#type' => 'select',
    '#title' => t('Hourly threshold'),
    '#options' => drupal_map_assoc(array(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 20, 30, 40, 50)),
    '#default_value' => 3,
    '#description' => t('The maximum number of contact form submissions a user can perform per hour.'),
  );
  //$form['contact']['contact_mail_limit'] = array(
  //  '#type' => 'select',
  //  '#title' => t('Sending e-mails limit'),
  //  '#options' => drupal_map_assoc(array(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 20, 30, 40, 50)),
  //  '#default_value' => 3,
  //);
  //$form['contact']['contact_mail_window'] = array(
  //  '#type' => 'select',
  //  '#title' => t('Sending e-mails window'),
  //  '#options' => array(0 => t('None (disabled)')) + drupal_map_assoc(array(60, 180, 300, 600, 900, 1800, 2700, 3600, 10800, 21600, 32400, 43200, 86400), 'format_interval'),
  //  '#default_value' => 3600,
  //);

  return system_settings_form($form);
}
