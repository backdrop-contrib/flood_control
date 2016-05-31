<?php

/**
 * @file
 * Admin page callbacks for the flood_control module.
 */

/**
 * Administration settings form.
 */
function flood_control_settings_form() {
  // User module flood events.
  $form['user'] = array(
    '#type' => 'fieldset',
    '#title' => t('User login'),
    '#access' => user_access('administer users'),
  );

  $form['user']['ip'] = array(
    '#type' => 'fieldset',
    '#title' => t('IP limits'),
    '#description' => t("Do not allow any login from the user's IP if the limit has been reached. Default is 50 failed attempts allowed in one hour. This is independent of the per-user limit to catch attempts from one IP to log in to many different user accounts. We have a reasonably high limit since there may be only one apparent IP for all users at an institution."),
  );
  $form['user']['ip']['flood_ip_limit'] = array(
    '#type' => 'select',
    '#title' => t('Failed login (IP) limit'),
    '#description' => t('Default 50.'),
    '#options' => backdrop_map_assoc(array(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 20, 30, 40, 50, 75, 100, 125, 150, 200, 250, 500)),
    '#default_value' => config_get('user.flood', 'flood_ip_limit'),
  );
  $form['user']['ip']['flood_ip_window'] = array(
    '#type' => 'select',
    '#title' => t('Failed login window'),
    '#description' => t('Default 1 hour.'),
    '#options' => array(0 => t('None (disabled)')) + backdrop_map_assoc(array(60, 180, 300, 600, 900, 1800, 2700, 3600, 10800, 21600, 32400, 43200, 86400), 'format_interval'),
    '#default_value' => config_get('user.flood', 'flood_ip_window'),
  );

  $form['user']['username'] = array(
    '#type' => 'fieldset',
    '#title' => t('Username limits'),
    '#description' => t("Don't allow login if the limit for a user has been reached. Default is to allow 5 failed attempts every 6 hours."),
  );
  $form['user']['username']['flood_uid_only'] = array(
    '#type' => 'select',
    '#title' => t('Flood event registration'),
    '#description' => t('Default - flood identifier is a combination of user id and IP address. This is less secure but more resistant to denial-of-service attacks that could lock out all users with public user names. More secure - register flood events based on the uid only, so they apply for any IP address.'),
    '#options' => array(0 => t('UID + IP address'), 1 => t('UID only')),
    '#default_value' => (int) config_get('user.flood', 'flood_uid_only'),
  );

  $form['user']['username']['flood_user_limit'] = array(
    '#type' => 'select',
    '#title' => t('Failed login limit'),
    '#description' => t('Default 5 attempts'),
    '#options' => backdrop_map_assoc(array(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 20, 30, 40, 50, 75, 100, 125, 150, 200, 250, 500)),
    '#default_value' => config_get('user.flood', 'flood_user_limit'),
  );
  $form['user']['username']['flood_user_window'] = array(
    '#type' => 'select',
    '#title' => t('Failed login window'),
    '#description' => t('Default 6 hours.'),
    '#options' => array(0 => t('None (disabled)')) + backdrop_map_assoc(array(60, 180, 300, 600, 900, 1800, 2700, 3600, 10800, 21600, 32400, 43200, 86400), 'format_interval'),
    '#default_value' => config_get('user.flood', 'flood_user_window'),
  );

  // Contact module flood events.
  $form['contact'] = array(
    '#type' => 'fieldset',
    '#title' => t('Contact forms'),
    '#access' => user_access('administer contact forms'),
  );
  $form['contact']['contact_threshold_limit'] = array(
    '#type' => 'select',
    '#title' => t('Sending e-mails limit'),
    '#options' => backdrop_map_assoc(array(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 20, 30, 40, 50, 75, 100, 125, 150, 200, 250, 500)),
    '#default_value' => config_get('contact.settings', 'contact_threshold_limit'),
  );
  $form['contact']['contact_threshold_window'] = array(
    '#type' => 'select',
    '#title' => t('Sending e-mails window'),
    '#options' => array(0 => t('None (disabled)')) + backdrop_map_assoc(array(60, 180, 300, 600, 900, 1800, 2700, 3600, 10800, 21600, 32400, 43200, 86400), 'format_interval'),
    '#default_value' => config_get('contact.settings', 'contact_threshold_window'),
  );

  // Show a message if the user does not have any access to any options.
  if (!element_get_visible_children($form)) {
    $form['nothing'] = array(
      '#markup' => '<p>' . t('Sorry, there are no flood control options for you to configure.') . '</p>',
    );
  }
  else {
    $form['actions']['#type'] = 'actions';
    $form['actions']['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Save configuration'),
      '#submit' => array('flood_control_settings_form_submit'),
    );
  }

  return $form;
}

/**
 * Implements hook_submit().
 */
function flood_control_settings_form_submit($form, &$form_state) {
  if (isset($form_state['values']['flood_ip_limit'])) {
    $user_config = config('user.flood');
    $user_config->set('flood_uid_only', (bool) $form_state['values']['flood_uid_only']);
    $user_config->set('flood_ip_limit', (int) $form_state['values']['flood_ip_limit']);
    $user_config->set('flood_ip_window', (int) $form_state['values']['flood_ip_window']);
    $user_config->set('flood_user_limit', (int) $form_state['values']['flood_user_limit']);
    $user_config->set('flood_user_window', (int) $form_state['values']['flood_user_window']);
    $user_config->save();
    watchdog('flood_control', t('User flood configuration updated.'), array(), WATCHDOG_INFO, l(t('Configure'), 'admin/config/system/flood-control'));

  }

  if (isset($form_state['values']['contact_threshold_limit'])) {
    $user_config = config('contact.settings');
    $user_config->set('contact_threshold_limit', (int) $form_state['values']['contact_threshold_limit']);
    $user_config->set('contact_threshold_window', (int) $form_state['values']['contact_threshold_window']);
    $user_config->save();
    watchdog('flood_control', t('Contact flood configuration updated.'), array(), WATCHDOG_INFO, l(t('Configure'), 'admin/config/system/flood-control'));

  }
}
