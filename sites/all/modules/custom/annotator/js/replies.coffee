#
# Allow users to view and create threaded replies to annotations
#
# Mike Widner <mikewidner@stanford.edu>
#
class Annotator.Plugin.Replies extends Annotator.Plugin

  replyClasses: {
    "base": "annotator-reply"
    "hidden": "annotator-reply-hidden"
    "reply": "fa fa-reply"
  }

  pluginInit: ->
    return unless Annotator.supported()
    @annotator.viewer.addField({
      load: @initReplies
    })

  show: (field) =>
    field.classList.remove(@replyClasses.hidden)
    textarea = field.getElementsByTagName('textarea')
    textarea[0].focus()

  hide: (field) =>
    field.classList.add(@replyClasses.hidden)

  toggleVisibility: (field) =>
    if @replyClasses.hidden in field.classList
      @show(field)
    else
      @hide(field)

  addReplyArea: (field, annotation, pid) =>
    # Add a textarea for replies; NOTE: hideReplyArea relies on this structure
    form = document.createElement("form")
    form.id = "#{@replyClasses.base}-form"
    textarea = document.createElement("textarea")
    textarea.classList.add(@replyClasses.base)
    buttons = document.createElement("div")
    buttons.classList.add("#{@replyClasses.base}-controls")
    save = document.createElement("a")
    save.classList.add("#{@replyClasses.base}-save")
    save.innerHTML = "Save"
    save.addEventListener("click", (event) => @saveReply(event, annotation, textarea, pid))
    cancel = document.createElement("a")
    cancel.classList.add("#{@replyClasses.base}-cancel")
    cancel.innerHTML = "Cancel"
    cancel.addEventListener("click", () => @cancelReply(textarea))
    buttons.appendChild(cancel)
    buttons.appendChild(save)
    form.appendChild(textarea)
    form.appendChild(buttons)
    field.appendChild(form)

  hideReplyArea: (textarea) =>
    # requires knowing about the form structure created in addReplyArea
    @hide(textarea.parentNode)

  addReplyLink: (field, annotation, pid = 0) =>
    span = document.createElement("span")
    span.innerHTML = "Reply"
    for className in @replyClasses.reply.split(" ")
      span.classList.add(className)
    span.addEventListener("click", () => @toggleVisibility(replyArea))
    field.appendChild(span)
    replyArea = @addReplyArea(field, annotation, pid)
    @hide(replyArea)

  initReplies: (field, annotation) =>
    n_replies = Object.keys(annotation.comments).length
    field.classList.add(@replyClasses.base)
    replies_text = "Replies"
    if n_replies == 1
      replies_text = "Reply"  # because English
    if n_replies > 0
      span = document.createElement("span")
      span.innerHTML = "#{n_replies} #{replies_text}"
      field.appendChild(span)
      replies = @drawReplies(field, annotation)
      span.addEventListener("click", (event) => @toggleVisibility(replies))
      @hide(replies)
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

  drawReply: (element, reply) ->
    li = document.createElement("li")
    li.innerHTML = reply['author'] + ' on ' + reply['date']
    li.classList.add('annotator-reply-id-' + reply['id'])
    text = document.createElement("span")
    text.innerHTML = reply['text']
    text.classList.add('annotator-reply-text')
    li.appendChild(text)
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
      @addReplyLink(li, annotation, reply['id'])
    return list

  saveReply: (event, annotation, textarea, pid) =>
    annotation.reply = {}
    annotation.reply.pid = pid # should be the parent id or 0
    annotation.reply.text = textarea.value
    annotation.reply.uid = Drupal.settings.annotator_replies.current_uid # current user ID
    @annotator.publish('annotationUpdated', [annotation])
    @hideReplyArea(textarea)

  cancelReply: (textarea) =>
    textarea.value = ""
    @hide(textarea.parentNode)

