<?php
$description = json_decode($record->description);
?>
<div id="tripal_jbrowse_pane_container">
    <p>
      <?php print check_markup($description->value, $description->format) ?>
    </p>
    <p>
        <a href="<?php print $record->link ?>" class="btn btn-primary">
            Go to JBrowse
        </a>
    </p>
</div>