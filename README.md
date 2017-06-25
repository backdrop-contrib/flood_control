Flood control
=============

Add an administration interface for hidden variables that limit login attempts and contact form submissions in Backdrop.

Login attempts and contact form submissions have thresholds saying that each user can only do that event a certain number of times in a set window. Various core functions verify that users have not exceeded thresholds for form submissions, but it does not expose the values of those thresholds or provide an interface for them to be changed.

By default Backdrop allows up to 50 failed login attempts regardless of the username within a 1 hour window. For a specific username, 5 failed login attempts within 6 hours causes the username to be temporarily blocked.

Hidden variables exposed by this module
---------------------------------------

### user.flood

- flood_ip_limit (default 50 attempts)
- flood_ip_window (default 1 hour)
- flood_uid_only (default false)
- flood_user_limit (default 5 attempts)
- flood_user_window (default 6 hours)

### contact.settings

- contact_threshold_limit
- contact_threshold_window

Current Maintainer
------------------

- None

Credits
-------

- Originally written for Drupal by Dave Reid (https://github.com/davereid)
- Ported to Backdrop by David Norman (https://github.com/deekayen)

License
-------

This project is GPL v2 software. See the LICENSE.txt file in this directory for
complete text.
