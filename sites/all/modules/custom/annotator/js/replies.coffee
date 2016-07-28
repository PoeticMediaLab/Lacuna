#
# Allow users to view and create threaded replies to annotations
#
# Mike Widner <mikewidner@stanford.edu>
#
class Annotator.Plugin.Replies extends Annotator.Plugin

  # CSS classes to apply to different fields
  replyClasses: {
    "base": "annotator-reply"
    "hidden": "annotator-reply-hidden"
    "reply": "fa fa-reply"
    "edit": "fa fa-edit"
    "del": "fa fa-trash"
  }

  # Select areas to put content
  replySelectors: {
    "replyarea": "div#content"
  }

  pluginInit: ->
    return unless Annotator.supported()
    @annotator.viewer.addField({
      load: @initReplies
    })

  defaultClass: (key) =>
    return @replyClasses.base + '-' + key

  addClasses: (element, key) =>
    # Adds classes based on the replyClasses keys
    if key not of @replyClasses
      # Provide a default
      classNames = @defaultClass(key)
    else
      classNames = @replyClasses[key]
    for className in classNames.split(" ")
      element.classList.add(className)

  removeClasses: (element, key) =>
    if key not of @replyClasses
      classNames = @defaultClass(key)
    else
      classNames = @replyClasses[key]
    for className in classNames.split(" ")
      element.classList.remove(className)

  show: (field) =>
    @removeClasses(field, 'hidden')
    field.style.display = "block";
    textarea = field.getElementsByTagName('textarea')
    if textarea.length > 0
      textarea[0].focus()

  hide: (field) =>
    @addClasses(field, 'hidden')
    field.style.display = "none";

  toggleVisibility: (field) =>
    if @replyClasses.hidden in field.classList
      @show(field)
    else
      @hide(field)

  addReplyArea: (annotation, pid) =>
    # Add a textarea for replies; NOTE: hideReplyArea relies on this structure
    formid = "#{@replyClasses.base}-form-#{annotation.id}-#{pid}"
    form = document.getElementById(formid)
    if form?
      return form
    form = document.createElement("form")
    form.id = formid
    @addClasses(form, 'form')
    textarea = document.createElement("textarea")
    textid = "#{@replyClasses.base}-textarea-#{annotation.id}-#{pid}"
    textarea.id = textid
    @addClasses(textarea, 'text')
    buttons = document.createElement("div")
    save = document.createElement("a")
    @addClasses(save, 'button')
    @addClasses(save, 'save')
    save.innerHTML = "Save"
    save.addEventListener("click", (event) => @saveReply(event, annotation, textarea, pid))
    cancel = document.createElement("a")
    @addClasses(cancel, 'button')
    cancel.innerHTML = "Cancel"
    cancel.addEventListener("click", () => @cancelReply(textarea))
    buttons.appendChild(cancel)
    buttons.appendChild(save)
    form.appendChild(textarea)
    form.appendChild(buttons)
    field = document.querySelector(@replySelectors.replyarea)
    field.appendChild(form)
    if Annotator.Plugin.RichText? and textid?
      CKEDITOR.replace(textid)
    return form

  hideReplyArea: (textarea) =>
    # requires knowing about the form structure created in addReplyArea
    @hide(textarea.parentNode)

  addReplyLink: (field, annotation, pid = 0) =>
    span = document.createElement("span")
    span.innerHTML = "Reply"
    @addClasses(span, 'reply')
    replyArea = @addReplyArea(annotation, pid)
    @hide(replyArea)
    span.addEventListener("click", () => @toggleVisibility(replyArea))
    field.appendChild(span)

  initReplies: (field, annotation) =>
    n_replies = Object.keys(annotation.comments).length
    replies_text = "Replies"
    if n_replies == 1
      replies_text = "Reply"  # because English
    if n_replies > 0
      span = document.createElement("span")
      span.innerHTML = "#{n_replies} #{replies_text}"
      field.appendChild(span)
      replies = @drawReplies(field, annotation)
      span.addEventListener("click", () => @toggleVisibility(replies))
      @hide(replies)
    @addClasses(field, 'base')
    @addReplyLink(field, annotation)

  convertRepliesData: (replies) ->
    repliesList = []
    for id, data of replies
    # Give us a data structure a little easier to work with
      date = new Date(data['created'] * 1000);
      date_string = date.getFullYear() + '-' + date.getMonth() + '-' + date.getDate() + ' ' + date.getHours() + ':' + date.getMinutes()
      reply = {
        'id': id
        'pid': data['pid']
        'text': data['comment_body']['und'][0]['safe_value'],
        'author': data['name'],
        'date': date_string,
        'thread': data['thread']  # special drupal field for ordering
        'permissions': data['permissions'] # edit/delete permissions
      }
      repliesList.push(reply)
    return repliesList

  sortReplies: (replies) ->
    # Use Drupal's thread field to sort
    # See: https://api.drupal.org/api/drupal/modules!comment!comment.module/function/comment_get_thread/7.x
    replies.sort (a,b) ->
      thread_a = a['thread'].substring(0, -1)
      thread_b = b['thread'].substring(0, -1)
      if thread_a < thread_b
        -1
      else if thread_a > thread_b
        1
      else 0

  replyDepth: (thread) ->
    # Return the depth of a reply based on the thread string
    (thread.match(/\./g) or []).length

  initList: (element) ->
    l = element.getElementsByTagName('ol')
    if l.length == 0
      l = document.createElement('ol')
      @addClasses(l, 'list')
      element.appendChild(l)
    else
      # It's a list of elements
      l = l[0]
    return l

  getListAtDepth: (element, depth) ->
    # Check if a list element of depth exists
    # If not, create it; return the list
    parent = element
    while depth--
      parent = @getListAtDepth(@initList(parent), depth)
    return parent

  addControls: (element, reply) ->
    # Add edit/delete controls to a reply
    controls = document.createElement('div')
    @addClasses(controls, 'controls')
    element.appendChild(controls)

    replyLink = document.createElement('span')
    @addClasses(replyLink, 'reply')
    controls.appendChild(replyLink)

    if !reply.permissions?
      return

    if reply.permissions.edit
      edit = document.createElement('span')
      @addClasses(edit, 'edit')
      controls.appendChild(edit)

    if reply.permissions.del
      del = document.createElement('span')
      @addClasses(del, 'del')
      controls.appendChild(del)

  drawReply: (element, reply) ->
    li = document.createElement("li")
    li.innerHTML = reply['author'] + ' on ' + reply['date']
    li.classList.add('annotator-reply-id-' + reply['id'])
    @addClasses(li, 'replyarea')
    text = document.createElement("span")
    text.innerHTML = reply['text']
    @addClasses(text, 'text')
    li.appendChild(text)
    @addControls(li, reply)
    element.appendChild(li)
    return li

  drawReplies: (element, annotation) =>
    replies = @convertRepliesData(annotation.comments)
    replies = @sortReplies(replies)
    list = @initList(element)
    for reply in replies
      depth = @replyDepth(reply['thread'])
      el = @getListAtDepth(list, depth)
      li = @drawReply(el, reply)
#      @addReplyLink(li, annotation, reply['id'])
    return list

  saveReply: (event, annotation, textarea, pid) =>
    annotation.reply = {}
    annotation.reply.pid = pid # should be the parent id or 0
    if Annotator.Plugin.RichText? and textarea.id?
      annotation.reply.text = CKEDITOR.instances[textarea.id].getData()
    else
      annotation.reply.text = textarea.value
    annotation.reply.uid = Drupal.settings.annotator_replies.current_uid # current user ID
    @annotator.publish('annotationUpdated', [annotation])
    # So we don't duplicate replies, delete this temporary data now that it's saved
    delete annotation.reply
    @hideReplyArea(textarea)

  cancelReply: (textarea) =>
    textarea.value = ""
    @hideReplyArea(textarea)

