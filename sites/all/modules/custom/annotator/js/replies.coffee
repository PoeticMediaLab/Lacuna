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

  toggleVisibility: (field, event = null) =>
    if @replyClasses.hidden in field.classList
      @show(field)  # show first so we have offsetWidth/Height values
      if event
        left = event.clientX - field.offsetWidth / 2
        top = event.pageY - field.offsetHeight
        field.style.left = left + 'px'
        field.style.top = top + 'px'
        @annotator.viewer.hide()
    else
      @hide(field)

  addReplyArea: (annotation, id, pid, default_text = '') =>
    # Add a textarea for replies; NOTE: hideReplyArea relies on this structure
    baseid = "#{@replyClasses.base}-#{annotation.id}-#{id}-#{pid}"
    if default_text.length
      baseid += '-update' # because we need two forms; one for replies, one to update a reply
    formid = baseid + '-form'
    form = document.getElementById(formid)
    if form?
      return form
    form = document.createElement("form")
    form.id = formid
    @addClasses(form, 'form')
    textarea = document.createElement("textarea")
    textid = baseid + '-text'
    textarea.id = textid
    textarea.textContent = default_text
    @addClasses(textarea, 'text')
    buttons = document.createElement("div")
    save = document.createElement("a")
    @addClasses(save, 'button')
    @addClasses(save, 'save')
    save.innerHTML = "Save"
    save.addEventListener("click", () => @saveReply(annotation, textarea, id, pid))
    save.addEventListener("touchend", (event) => 
      @saveReply(annotation, textarea, id, pid)
      event.stopPropagation()
    )
    cancel = document.createElement("a")
    @addClasses(cancel, 'button')
    cancel.innerHTML = "Cancel"
    cancel.addEventListener("click", () => @cancelReply(textarea))
    cancel.addEventListener("touchend", (event) => 
      @cancelReply(textarea)
      event.stopPropagation()
    )
    buttons.appendChild(cancel)
    buttons.appendChild(save)
    form.appendChild(textarea)
    form.appendChild(buttons)
    field = document.querySelector(@replySelectors.replyarea)
    field.appendChild(form)
    if Annotator.Plugin.RichText? and textid?
      CKEDITOR.replace(textid)
    return form

  clearReplyArea: (textarea) ->
    # Remove the text from a textarea
    # Necessary because CKEditor will persist with it's default value
    textarea.textContent = ''
    if Annotator.Plugin.RichText?
      CKEDITOR.instances[textarea.id].setData('')

  hideReplyArea: (textarea) =>
    # requires knowing about the form structure created in addReplyArea
    @hide(textarea.parentNode)

  addReplyLink: (field, annotation, pid = 0) =>
    span = document.createElement("span")
    span.innerHTML = "Reply"
    @addClasses(span, 'reply')
    replyArea = @addReplyArea(annotation, 0, pid)
    @hide(replyArea)
    span.addEventListener("click", (event) => @toggleVisibility(replyArea, event))
    span.addEventListener("touchend", (event) => 
      @toggleVisibility(replyArea, event)
      event.stopPropagation()
    )
    field.appendChild(span)

  initReplies: (field, annotation) =>
    if annotation.comments?
      n_replies = Object.keys(annotation.comments).length
    else
      n_replies = 0
    replies_text = "Replies"
    if n_replies == 1
      replies_text = "Reply"  # because English
    if n_replies > 0
      span = document.createElement("span")
      span.innerHTML = "#{n_replies} #{replies_text}"
      field.appendChild(span)
      replies = @drawReplies(field, annotation)
      span.addEventListener("click", () => @toggleVisibility(replies))
      span.addEventListener("touchend", (event) => 
        @toggleVisibility(replies)
        event.stopPropagation()
      )
      @hide(replies)
    @addClasses(field, 'base')
    @addReplyLink(field, annotation)

  convertRepliesData: (replies) ->
    repliesList = []
    for id, data of replies
    # Give us a data structure a little easier to work with
      date = new Date(data['created'] * 1000);
      
      date_string = date.toLocaleString(navigator.language, {month:'long', day: 'numeric', hour: 'numeric', minute: 'numeric', hour12: false})
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

  getListAtDepth: (l, depth) ->
    # Check if a list element of depth exists
    # If not, create it; return the list
    while depth > 0
      depth -= 1
      l = @initList(l)
    return l

  addControls: (element, reply, annotation) ->
    # Add edit/delete controls to a reply
    controls = document.createElement('div')
    @addClasses(controls, 'controls')
    element.appendChild(controls)

    replyLink = document.createElement('span')
    @addClasses(replyLink, 'reply')
    controls.appendChild(replyLink)
    # reply.id == 0 indicates a new reply
    replyArea = @addReplyArea(annotation, 0, reply.id, '')
    @hide(replyArea)
    replyLink.addEventListener("click", (event) => @toggleVisibility(replyArea, event))
    replyLink.addEventListener("touchend", (event) => 
      @toggleVisibility(replyArea, event)
      event.stopPropagation()
    )

    if !reply.permissions?
      return

    if reply.permissions.edit
      edit = document.createElement('span')
      @addClasses(edit, 'edit')
      editArea = @addReplyArea(annotation, reply.id, reply.pid, reply.text)
      @hide(editArea)
      edit.addEventListener("click", (event) => @toggleVisibility(editArea, event))
      edit.addEventListener("touchend", (event) => 
        @toggleVisibility(editArea, event)
        event.stopPropagation()
      )
      controls.appendChild(edit)

#     Leaving comment deletion unavailable (it works)
#     Because the best we can do with Drupal is change the text to "reply deleted"
#    if reply.permissions.del
#      del = document.createElement('span')
#      @addClasses(del, 'del')
#      del.addEventListener("click", () => @deleteReply(annotation, reply))
#      controls.appendChild(del)

  drawReply: (element, reply, annotation) ->
    li = document.createElement("li")
    author_span = document.createElement('span')
    author_span.innerHTML = reply['author']
    @addClasses(author_span, 'author')
    date_span = document.createElement('span')
    date_span.innerHTML = reply['date']
    @addClasses(date_span, 'date')
    li.appendChild(author_span)
    li.appendChild(date_span)
    li.classList.add('annotator-reply-id-' + reply['id'])
    @addClasses(li, 'replyarea')
    text = document.createElement("span")
    text.innerHTML = reply['text']
    @addClasses(text, 'text')
    li.appendChild(text)
    @addControls(li, reply, annotation)
    element.appendChild(li)

  drawReplies: (element, annotation) =>
    replies = @convertRepliesData(annotation.comments)
    replies = @sortReplies(replies)
    list = @initList(element)
    for reply in replies
      depth = @replyDepth(reply['thread'])
      el = @getListAtDepth(list, depth)
      @drawReply(el, reply, annotation)
    return list

  deleteReply: (annotation, reply) =>
    # Add a annotation.reply.type = 'delete'
    # Then publish annotationUpdated, let the store handle deleting it
    reply.type = 'delete'
    annotation.reply = reply
    @annotator.publish('annotationUpdated', [annotation])
    delete annotation.reply

  saveReply: (annotation, textarea, id, pid) =>
    annotation.reply = {}
    annotation.reply.pid = pid # should be the parent id or 0
    annotation.reply.type = 'new'
    if id != 0
      annotation.reply.id = id
      annotation.reply.type = 'update'
    if Annotator.Plugin.RichText? and textarea.id?
      annotation.reply.text = CKEDITOR.instances[textarea.id].getData()
    else
      annotation.reply.text = textarea.value
    annotation.reply.uid = Drupal.settings.annotator_replies.current_uid # current user ID
    @annotator.publish('annotationUpdated', [annotation])
    # So we don't duplicate replies, delete this temporary data now that it's saved
    delete annotation.reply
    @clearReplyArea(textarea)
    @hideReplyArea(textarea)

  cancelReply: (textarea) =>
    textarea.value = ""
    @hideReplyArea(textarea)

