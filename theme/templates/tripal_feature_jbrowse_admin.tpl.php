<?php

if ($has_records):
  print $list_table;
else:
  ?>
  <p>
    There are no records to display yet. You can add a new association by clicking the "Add" link above.
  </p>
<?php endif; ?>