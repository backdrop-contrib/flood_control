Flood control
=============

Add an administration interface for hidden flood control variables in Backdrop
like the limits on login attempts and contact form submissions.

By default Backdrop allows up to 50 failed login attempts regardless of the
username within a 1 hour window. For a specific username, 5 failed login
attempts within 6 hours causes the username to be temporarily blocked.

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

- David Norman (https://github.com/deekayen)

Credits
-------

- Originally written for Drupal by Dave Reid (https://github.com/davereid)
- Ported to Backdrop by David Norman (https://github.com/deekayen)

License
-------

This project is GPL v2 software. See the LICENSE.txt file in this directory for
complete text.
