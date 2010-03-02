<?php

/**
 * Implementation of hook_views_data().
 */
function openid_provider_sso_views_data() {
  $data = array();
  $data['openid_provider_sso_rps'] = array(
    'table' => array(
      'group' => t('OpenID'),
      'base' => array(
        'field' => 'realm',
        'title' => t('OpenID Relying Party'),
        'help' => t('Relying Parties accepted by this OpenID Provider.'),
      ),
    ),
    'realm' => array(
      'title' => t('Realm'),
      'help' => t('The URL of the relying party.'),
      'field' => array('handler' => 'views_handler_field_url'),
      'argument' => array('handler' => 'views_handler_argument'),
      'filter' => array('handler' => 'views_handler_filter'),
      'sort' => array('handler' => 'views_handler_sort'),
    ),
    'name' => array(
      'title' => t('Name'),
      'help' => t('The name of the relying party.'),
      'field' => array('handler' => 'views_handler_field'),
      'argument' => array('handler' => 'views_handler_argument'),
      'filter' => array('handler' => 'views_handler_filter'),
      'sort' => array('handler' => 'views_handler_sort'),
    ),
  );
  // OpenID Provider doesn't implement hook_views_data(), do so on its behalf.
  if (!module_hook('openid_provider', 'views_data')) {
    $data['openid_provider_relying_party'] = array(
      'table' => array(
        'group' => t('OpenID'),
        'join' => array(
          'openid_provider_sso_rps' => array(
            'left_field' => 'realm',
            'field' => 'realm',
          ),
        ),
      ),
      'uid' => array(
        'title'    => t('User'),
        'help'     => t('The user who has been authenticated for the relying party.'),
        'relationship' => array(
          'handler' => 'views_handler_relationship',
          'base' => 'users',
          'field' => 'uid',
          'label' => t('user'),
        ),
      ),
      'first_time' => array(
        'title' => t('First access time'),
        'help' => t('Timestamp of the first time this relying party was accessed.'),
        'field' => array('handler' => 'views_handler_field_date'),
        'sort' => array('handler' => 'views_handler_sort_date'),
        'filter' => array('handler' => 'views_handler_filter_date'),
      ),
      'last_time' => array(
        'title' => t('Last access time'),
        'help' => t('Timestamp of the most recent access.'),
        'field' => array('handler' => 'views_handler_field_date'),
        'sort' => array('handler' => 'views_handler_sort_date'),
        'filter' => array('handler' => 'views_handler_filter_date'),
      ),
      'auto_release' => array(
        'title' => t('Auto release'),
        'help' => t('Whether or not to automatically release this relying party.'),
        'field'  => array('handler' => 'views_handler_field_boolean'),
        'sort' => array('handler' => 'views_handler_sort'),
        'filter' => array(
          'handler' => 'views_handler_filter_boolean_operator',
          'label' => t('Auto release'),
          'type' => 'yes-no',
        ),
      ),
    );
  }
  return $data;
}
