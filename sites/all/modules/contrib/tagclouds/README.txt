Readme
------
Tagclouds is a small module forked from Tagadelic, without any databases, or configuration, that generates pages with weighted tags.
Tagclouds is an out of the box, ready to use module, if you want simple weighted tag clouds. With, or without some small CSS moderations this will probably suit most cases.
Unlike Tagadelic, Tagclouds does not claim to be an API.
Tagclouds supports the module i18n, if available see notes below for entity translation configuration and testing.

HOWTO - tags per entity with entity translation enabled
To test this patch:

 1    enable entity translation if it isn't already (or use a distro like this)
 2    create taxonomy vocabulary with translation mode "Translate." enabled (Different terms will be allowed for each language and they can be translated.)
 3    add taxonomy term reference field to basic page content type
 4    (options: use autocomplete widget)
 5    (more options: enable translation on taxonomy term reference field)
 6    install and enable tagclouds
 7    enable "Separation of Tags per language using entity translation" in eng/admin/config/content/tagclouds
 8    add tagclouds block to a panel or page
 9    add new basic page , add two taxonomy terms to your autocomplete taxonomy term reference field "taxonomy1-eng, taxonomy2-eng"
10   translate the same basic page (entity translation so the same "entity id /node id") , add terms "taxonomy1-lang2, taxonomy2-lang2"
11   add a second basic page, and translate it as done in step 7 and step 8, (use same taxonomy (tag) names "taxonomy1-eng, taxonomy2-eng" for english and "taxonomy1-lang2, taxonomy2-lang2" for the "other " language
12   compare results, you should see tag clouds for both english and lang2

KNOWN ISSUES: when your tag is common to both languages it will only show up in the language it was first saved to.  
For example the word "corruption" is spelled exactly the same in English as well as French and possibly other languages.
Until an enhancement to this module is created you can workaround this by naming the tag "le corruption" .
